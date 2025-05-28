-- Define a function to escape special XML characters
local function escape_xml(str)
    local entities = {
        ["&"] = "&amp;",
        ["<"] = "&lt;",
        [">"] = "&gt;",
        ["\""] = "&quot;",
        ["'"] = "&apos;"
    }
    return str:gsub("[&<>'\"]", entities)
end

-- Function to create an XML element
local function create_element(tag, content, attributes)
    local attr_str = ""
    if attributes then
        for k, v in pairs(attributes) do
            attr_str = attr_str .. string.format(' %s="%s"', k, escape_xml(v))
        end
    end
    if content then
        return string.format("<%s%s>%s</%s>", tag, attr_str, escape_xml(content), tag)
    else
        return string.format("<%s%s />", tag, attr_str)
    end
end

-- Create the XML structure
local xml = {
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
    "<root>",
    create_element("greeting", "Hello, world!", {lang = "en"}),
    create_element("farewell", "Goodbye!", {lang = "en"}),
    "</root>"
}

-- Concatenate the XML parts into a single string
local xml_string = table.concat(xml, "\n")

-- Write the XML string to a file
local file = io.open("output.xml", "w")
file:write(xml_string)
file:close()

print("XML file generated successfully!")

