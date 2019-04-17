p = 801410357975153
q = 950867021741191
n = p * q
phi = (p - 1) * (q - 1)
e = 110066171603901969362593059313
x1 = 651256495894733822754552878879
y2 = 253970845268857814403399216528

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

d = gcd(e, phi)['x'] % phi

# print(mySuperFastPow(mySuperFastPow(x1, e, n), d, n))
y1 = mySuperFastPow(x1, e, n)
print('y1 = %d' % y1)
x1s = mySuperFastPow(y1, d, n)
print('decryped y1 = %d' % x1s)
if x1s == x1:
  print('Encryption/decryption correct')
else:
  print('Error')

print('x2 = %d' % mySuperFastPow(y2, d, n))
