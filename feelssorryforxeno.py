#He did it manually before, rip xenorino in pepperino

output = open("feelssorryforxeno_done.txt", 'w+')
output.write("std::string WeaponList[] = {")

f = open("feelssorryforxeno.txt", "r")
content = f.readlines()
for ripxeno in content:
    output.write('"' + ripxeno[:-2] + '",\n')
f.close()

output.write("}")
output.close()

print("DONE")
