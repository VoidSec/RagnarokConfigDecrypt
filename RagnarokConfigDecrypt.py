"""
Title:              Ragnarok Ransomware Configuration Decrypter
Author:             Paolo Stagno aka VoidSec - voidsec@voidsec.com - https://voidsec.com
Date:               23/04/2021
IOC:                
"""
#!/usr/bin/python
import argparse
parser = argparse.ArgumentParser(prog="RagnarokConfigDecrypt.py",
                                description="Decrypt the encrypted configuration of the Ragnarok Ransomware")
parser.add_argument("-k", "--key", default="comehereplz", dest="key", help="Key")
parser.add_argument("-c", "--config", required=True, type=argparse.FileType('r'), dest="config", 
                                help="Dumped Encrypted Configuration File (usually start at 0x10017000)")
args = parser.parse_args()

# retrieve encrypted configuration file
enc_config_file = args.config

print("[-] Configuration Key: {}".format(args.key))
key = []
# split the key string char by char into a list
key[:] = args.key

print("[-] Generating in-memory structures")
charset = [0] * 256
big_key = [0] * 256
decryption_key = [0] * 256

i = 0
while i < 256:
    charset[i] = i
    big_key[i] = key[i % len(key)]
    i += 1

print("[-] Generating decryption key")
i = 0
z = 0
while z < 256:
    tmp1 = charset[z]
    i = (i + ord(big_key[z]) + tmp1) % 126
    charset[z] = charset[i]
    charset[i] = tmp1
    z += 1
decryption_key = charset
decryption_key_hex = ""
for byte in decryption_key:
    decryption_key_hex += "{0:0{1}X} ".format((byte), 2)
# "{0:0{1}x}".format(1,2) fill single byte with leading 0
# "{0:#0{1}x}".format(1,4) -> '0x01

print("[+] Decryption Key:")
print("----------------------------")
print(decryption_key_hex)
print("----------------------------")

f = open("decryption_key.bin", "w")
f.write(decryption_key_hex)
f.close()
print("[-] saved in: decryption_key.bin\n")

print("[-] Reading Encrypted Configuration File")
enc_config = []
tmp = enc_config_file.read().lstrip().rstrip()

for byte in tmp.split(" "):
    enc_config.append(int(byte, 16))
enc_config_file.close()

print("[-] Decrypting Ransomware Configuration")
x = 0
k = 0
w = 0
while w < 6512:
    tmp1 = (k + 1) % 126
    tmp2 = decryption_key[tmp1]
    x = (tmp2 + x) % 126
    decryption_key[tmp1] = decryption_key[x]
    decryption_key[x] = tmp2
    enc_config[w] ^= decryption_key[(
        tmp2 + decryption_key[(k + 1) % 126]) % 126]
    k = tmp1
    w += 1

# convert back from int to ASCII char
enc_config = [chr(byte) for byte in enc_config]
dec_config = ""
# join item in list forming a string
dec_config = dec_config.join(enc_config)

print("[+] Configuration:")
print("----------------------------")
print(dec_config)
print("----------------------------")

f = open("config.json", "w")
f.write(dec_config)
f.close()
print("[-] saved in: config.json")
# =^.^=