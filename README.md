# Ragnarok Configuration Decrypt
Ragnarok Ransomware Configuration Decrypter

## Usage
```
python RagnarokConfigDecrypt.py --help
usage: RagnarokConfigDecrypt.py [-h] [-k KEY] -c CONFIG

Decrypt the encrypted configuration of the Ragnarok Ransomware

optional arguments:
  -h, --help            show this help message and exit
  -k KEY, --key KEY     Key
  -c CONFIG, --config CONFIG
                        Dumped Encrypted Configuration File (usually start at 0x10017000)
```