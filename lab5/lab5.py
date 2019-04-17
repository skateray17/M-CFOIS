import random
import hashlib

q = 225523118922100465769758148413025421807220956799975071969675156327098020673011

def mySuperFastPow(a, b, n):
  if not b:
    return 1
  if b % 2:
    return a * mySuperFastPow(a * a % n, (b - 1) // 2, n) % n
  return mySuperFastPow(a * a % n, b // 2, n) % n

def gcd (a, b):
  if not a:
    return { 'x': 0, 'y': 1, 'd': b }
  r = gcd (b % a, a)
  y = r['x']
  x = r['y'] - (b // a) * y
  return { 'x': x, 'y': y, 'd': r['d'] }

def gen(q):
  p = 0
  R = 4 * q + 2
  while True:
    R -= 2
    p = q * R + 1
    if mySuperFastPow(2, q * R, p) == 1 and mySuperFastPow(2, R, p) != 1:
      break
  x = random.randrange(p)
  g = mySuperFastPow(x, R, p)
  while g == 1:
    x = random.randrange(p)
    g = mySuperFastPow(x, R, p)
  d = random.randrange(q)
  e = mySuperFastPow(g, d, p)
  return { 'p': p, 'q': q, 'g': g, 'e': e, 'd': d }

def sign(p, q, g, d, M):
  m = int(hashlib.sha256(M).hexdigest(), 16)
  k = random.randrange(1, q)
  r = mySuperFastPow(g, k, p)
  k_rev = gcd(k, q)['x']
  s = (k_rev * (m - d * r)) % q
  return { 'r': r, 's': s }

def verify(p, q, g, e, M, r, s):
  if r >= p or r <= 0 or s >= q or s < 0:
    return False
  m = int(hashlib.sha256(M).hexdigest(), 16)
  return (mySuperFastPow(e, r, p) * mySuperFastPow(r, s, p)) % p == mySuperFastPow(g, m, p)

params = gen(q)
message = "I, Alexander Kovalchuk, love MiKOZI".encode("utf-8")
signed = sign(params['p'], params['q'], params['g'], params['d'], message)
print(verify(params['p'], params['q'], params['g'], params['e'], message, signed['r'], signed['s']))
