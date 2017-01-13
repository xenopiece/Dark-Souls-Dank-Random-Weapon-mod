#He did it manually before, rip xenorino in pepperino

output = open("feelssorryforxenoinfusions_done.txt", 'w+')
output.write("std::vector<std::string> WeaponListInfusions = {")

f = open("feelssorryforxenoinfusions.txt", "r")
content = f.readlines()
for ripxeno in content:
	if (ripxeno.find("Sharp")):
    	output.write('\t"' + ripxeno[:-2] + '",\n')
f.close()

output.write("}")
output.close()

print("DONE")
