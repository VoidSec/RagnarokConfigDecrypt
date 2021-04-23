x = 0
k = 0
w = 0

while w < 6512:
	tmp1 = (k + 1) % 126;
	tmp2 = decryption_key[tmp1];
    x = (tmp2 + x) % 126;
    decryption_key[tmp1] = decryption_key[x];
    decryption_key[x] = tmp2;
    enc_config[w] ^= decryption_key[(tmp2 + decryption_key[(k + 1) % 126]) % 126];
    k = tmp1;
	w+=1
