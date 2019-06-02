int a = 4
int b = 20
print a
print b

a = b
print a

string sa = "string a"
string sb = "string b"
print sa
print sb

sb = sa
print sb

bool truthy = true
bool falsy = false

print truthy
print falsy

falsy = truthy
print falsy

int c = a
print a

int d = (10 / 5) - 5
print d

bool adb = 5 > 4

bool adc = !adb
print adc

int gh = 5
if !adc {
  gh = gh + 5
}
else {
  gh = gh + 7
}
while gh < 30 {
  gh = gh + 7
}

print gh
