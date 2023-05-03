#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/satellite-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

int main(int argc, char *argv[])
{
  // Create two ground stations
  NodeContainer groundStations;
  groundStations.Create(2);

  // Create a satellite node
  NodeContainer satellite;
  satellite.Create(1);

  // Set up a point-to-point link between each ground station and the satellite
  PointToPointHelper groundToSatellite;
  groundToSatellite.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
  groundToSatellite.SetDeviceAttribute("Delay", StringValue("50ms"));

  NetDeviceContainer gs0ToSatellite = groundToSatellite.Install(groundStations.Get(0), satellite.Get(0));
  NetDeviceContainer gs1ToSatellite = groundToSatellite.Install(groundStations.Get(1), satellite.Get(0));

  // Set up the satellite channel
  PointToPointHelper satelliteChannel;
  satelliteChannel.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
  satelliteChannel.SetDeviceAttribute("Delay", StringValue("500ms"));

  NetDeviceContainer satelliteLink = satelliteChannel.Install(satellite);

  // Set up the satellite channel model
  Ptr<SatelliteChannel> channel = CreateObject<SatelliteChannel>();
  channel->SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
  channel->SetAttribute("PropagationDelay", TimeValue(500 * MilliSeconds));
  channel->SetAttribute("DataRate", DataRateValue(100 * MegaBps));
  channel->SetAttribute("InterferenceModel", StringValue("ns3::SatelliteInterferenceHelper"));

  // Install the satellite channel model on the satellite link
  satelliteLink.Get(0)->AggregateObject(channel);

  // Set up a simple application to generate traffic between the ground stations
  uint16_t port = 5000;
  OnOffHelper onOffHelper("ns3::UdpSocketFactory", Address());
  onOffHelper.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onOffHelper.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  onOffHelper.SetAttribute("PacketSize", UintegerValue(1024));
  onOffHelper.SetAttribute("DataRate", DataRateValue(5 * Mbps));

  ApplicationContainer apps;
  AddressValue remoteAddress(InetSocketAddress(groundStations.Get(1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(), port));
  onOffHelper.SetAttribute("Remote", remoteAddress);
  apps.Add(onOffHelper.Install(groundStations.Get(0)));

  // Start the simulation and run for 10 seconds
  Simulator::Stop(Seconds(10.0));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}

