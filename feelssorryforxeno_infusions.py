#He did it manually before, rip xenorino in pepperino

output = open("feelssorryforxeno_infusions_done.txt", 'w+')
output.write("std::vector<std::string> WeaponListInfusions = {\n")

f = open("feelssorryforxeno_infusions.txt", "r")
content = f.readlines()
for ripxeno in content:
	if (ripxeno.find("Sharp") != -1):
		output.write('\t"' + ripxeno[:-2] + '",\n')
f.close()

output.write("}")
output.close()

print("DONE")
