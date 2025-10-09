function printx(x)
	print(string.format("0x%X", x))
end

printx(0xDF & 0xFD)
