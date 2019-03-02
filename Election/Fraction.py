class Fraction:
    def __init__(self, num, de):
        self.numer = num
        self.denom = de

    def __str__(self):
        return str(self.numer) + "/" + str(self.denom)

    def __float__(self):
        return self.numer/self.denom
    
    def __int__(self):
        self.simplify()
        return self.numer

    def simplify(self):
        num1 = self.numer
        num2 = self.denom

        num3 = num1%num2
        while(num3 != 0):
            num1 = num2
            num2 = num3
            num3 = num1%num2

        if self.denom < 0:
            self.numer = self.numer*-1
            self.denom = self.denom*-1
        return Fraction(int(self.numer/ num2), int(self.denom/num2))

    def __sub__(self, other):
        if isinstance(other, Fraction):
            otherNumer = other.numer
            otherDenom = other.denom
        elif isinstance(other, int):
            otherNumer = other
            otherDenom = 1
        if (self.denom != otherDenom):
            tempDenom = self.denom
            tempNumer = self.numer
            self.denom = tempDenom*otherDenom
            self.numer = tempNumer*otherDenom
            otherNumer = otherNumer*tempDenom
        self.numer = self.numer - otherNumer
        self = self.simplify()
        return Fraction(self.numer, self.denom)

    def __rsub__(self, other):
        if isinstance(other, int):
            otherNumer = other
            otherDenom = 1
        if (self.denom != otherDenom):
            tempDenom = self.denom
            tempNumer = self.numer
            self.denom = tempDenom*otherDenom
            self.numer = tempNumer*otherDenom
            otherNumer = otherNumer*tempDenom
        self.numer = otherNumer - self.numer
        self = self.simplify()
        return Fraction(self.numer, self.denom)

    def __add__(self, other):
        if isinstance(other, Fraction):
            otherNumer = other.numer
            otherDenom = other.denom
        elif isinstance(other, int):
            otherNumer = other
            otherDenom = 1
        if (self.denom != otherDenom):
            tempDenom = self.denom
            tempNumer = self.numer
            self.denom = tempDenom*otherDenom
            self.numer = tempNumer*otherDenom
            otherNumer = otherNumer*tempDenom
        self.numer = self.numer + otherNumer
        self = self.simplify()
        return Fraction(self.numer, self.denom)

    def __radd__(self, other):
        if isinstance(other, int):
            otherNumer = other
            otherDenom = 1
        if (self.denom != otherDenom):
            tempDenom = self.denom
            tempNumer = self.numer
            self.denom = tempDenom*otherDenom
            self.numer = tempNumer*otherDenom
            otherNumer = otherNumer*tempDenom
        self.numer = self.numer + otherNumer
        self = self.simplify()
        return Fraction(self.numer, self.denom)

    def __mul__(self, other):
        if isinstance(other, Fraction):
            self.numer = self.numer*other.numer
            self.denom = self.denom*other.denom
        elif isinstance(other, int):
            self.numer = self.numer*other

        self = self.simplify()
        return Fraction(self.numer, self.denom)

    def __rmul__(self, other):
        if isinstance(other, int):
            self.numer = self.numer*other

        self = self.simplify()
        return Fraction(self.numer, self.denom)

    def __truediv__(self, other):
        if isinstance(other, Fraction):
            self.numer = self.numer * other.denom
            self.denom = self.denom * other.numer
        elif isinstance(other, int):
            self.denom = self.denom * other

        self = self.simplify()
        return Fraction(self.numer, self.denom)

    def __rtruediv__(self, other):
        if isinstance(other, int):
            temp = self.denom * other
            self.denom = self.numer
            self.numer = temp

        self = self.simplify()
        return Fraction(self.numer, self.denom)
