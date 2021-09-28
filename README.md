# Description
This repository will record some codes mentioned in Book 'From Mathematics to Generic programming' and use some examples to test it.

## Installation 
Install rsa package
```bash
CC=Clang pip install -e . -vvv
```
or 
```bash
python setup.py install
```

then for d2l
```
pip install -U d2l
```

,and finally for Pytorch(optional here for MAC with only CPU)
```bash
conda install pytorch torchvision torchaudio -c pytorch
```

## RSA algorithm
First we generate two large prime numbers: 
1. Choose two distinct prime numbers $p$ and $q$.
2. Compute $n = pq$.
3. Compute tue Eulear totient function $\phi(n)=(p-1)(q-1)$.

Now, we destroy $p_1$ and $p_2$; $n$ is published.  

1. Generate a random public key $pub$, coprime with $\phi(n)$ 
2. Find the private key $prv$, which is  multiplicative inverse of $pub$ modulo $\phi(n)$.

Finally, $pub$ is published and $prv$ is kept secret. When transferring message $m$, we are communicating:
1. the sender will encrypte message by raising $m$ to the power $pub$; 
2. the accepter will decrpte message by rasising private $prv$:

The above uses a theorem:
$$
(m^{pub})^{prv} = m \text{ mod } n
$$

> Attension:
> In reality, we represent each word by an intger and so in order to avoid different words $m$ and $m'$  encrypted by the same number like $m^{pub} = m^{'pub} \text{ mod } n$, we must require that the lenght of dictionary < $n = pq$