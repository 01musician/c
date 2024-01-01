function checkFile(filename)
	local file = io.open(filename, "rb")

	if file then
		local fileSize = file:seek("end")
		print("File name: " .. filename)
		print("File size: " .. fileSize .. "bytes")

		file:close()
	else
		print("Error: could not open the file")
	end
end

local fileName = "checkFile.lua"
checkFile(fileName)
