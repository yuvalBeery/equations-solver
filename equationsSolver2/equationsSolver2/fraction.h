#pragma once
#include <iostream>
#include <string>

enum numberType { integer, decimal, Fraction };
const int MAX_DIGITS_IN_LONG_LONG = 18;
const int NUMBERS_AFTER_DECIMAL_POINT = 12;
const int PERIODICITY_LIMIT = 4;
const int MAX_DIGITS_TO_SHOW_FRACTION = 5;


numberType findTipe(std::string number)
{
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] == '.')
			return decimal;

		else if (number[i] == '/')
			return Fraction;
	}

	return integer;
}


bool isFractionValid(std::string& number)
{
	int sleshCounter = 0;
	int decimalCounter = 0;
	int minusCounter = 0;
	int sleshPlace = 0;
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] != '0' && number[i] != '1' && number[i] != '2' && number[i] != '3' && number[i] != '4' && number[i] != '5' && number[i] != '6' && number[i] != '7' && number[i] != '8' && number[i] != '9' && number[i] != '/' && number[i] != '.' && number[i] != '-')
		{
			return false;
		}

		if (number[i] == '/')
		{
			if (i == 0 || i == number.length() - 1)
				return false;
			sleshCounter++;
			sleshPlace = i;
		}
		else if (number[i] == '.')
		{
			if (i == 0)
			{
				number = '0' + number;
				i++;
			}

			decimalCounter++;
		}
		else if (number[i] == '-')
		{
			if (i != 0 && i != sleshPlace + 1)
				return false;
			minusCounter++;
		}

	}

	if (sleshCounter > 1 || decimalCounter > 1 || minusCounter > 1 || (sleshCounter == 1 && decimalCounter == 1 && minusCounter == 1))
		return false;


	if (number[0] == '.')
		number = '0' + number;

	if (number[0] == '-' && number[1] == '.')
	{
		std::string tmpNumber = "0";
		for (int i = 1; i < number.length(); i++)
		{
			tmpNumber += number[i];
		}
		number = tmpNumber;
	}

	return true;
}


void setFraction(long double number, long long& numerator, long long& base)
{
	for (int i = 0; i < 1000; i++)
	{
		if (int(number * i) == number * i)
		{
			numerator = long long(number * i);
			base = i;
			return;
		}
	}
	numerator = long long(numerator * pow(10, NUMBERS_AFTER_DECIMAL_POINT));
	base = pow(10, NUMBERS_AFTER_DECIMAL_POINT);
}


class fraction
{
public:

	long long numerator;
	long long  base;

	fraction()
	{
		this->numerator = 1;
		this->base = 1;
	}


	fraction(long long n, long long b)
	{
		this->numerator = n;
		this->base = b;
		reduce();
	}


	fraction(long double number)
	{
		long long tmpNumerator, tmpBase;
		setFraction(number, tmpNumerator, tmpBase);
		this->numerator = tmpNumerator;
		this->base = tmpBase;
		reduce();
	}

	fraction(long long number)
	{
		this->numerator = number;
		this->base = 1;
	}


	fraction(std::string number)
	{
		numberType t = findTipe(number);

		if (t == decimal)
		{
			long long  tmpNumerator = 1;
			long long  tmpBase = 1;
			setFraction(std::stold(number), tmpNumerator, tmpBase);
			this->numerator = tmpNumerator;
			this->base = tmpBase;
			reduce();
			return;
		}

		if (t == integer)
		{
			number = number + "/" + "1";
		}

		std::string strNumerator;
		std::string strBase = "none";
		int i = 0;
		while (i < number.length())
		{
			if (number[i] == '/')
			{
				break;
			}

			strNumerator += number[i];
			i++;
		}

		for (int j = i + 1; j < number.length(); j++)
		{
			if (strBase == "none")
				strBase = number[j];

			else
				strBase += number[j];
		}

		this->numerator = std::stoll(strNumerator);
		this->base = std::stoll(strBase);

		this->reduce();
	}

	long long GCD(long long n, long long d)
	{
		long long t;
		n = abs(n);
		d = abs(d);

		if (d == 0)
			return 1;

		while (d != 0)
		{
			t = d;
			d = n % d;
			n = t;
		}

		return n;
	}

	void reduce()
	{
		long long gcd = GCD(this->numerator, this->base);
		if ((this->numerator < 0 && this->base < 0) || (this->numerator > 0 && this->base < 0))
		{
			this->numerator /= -gcd;
			this->base /= -gcd;
		}

		else
		{
			this->numerator /= gcd;
			this->base /= gcd;
		}
	}

	//returns max power of the fraction that remains in the MAX_DIGITS restriction
	int maxFractionPower()
	{
		long double zeroNumber = log10(this->base);
		int x = int(MAX_DIGITS_IN_LONG_LONG / zeroNumber);
		return x;
	}

	std::string show(bool isSimulated)
	{
		if (this->numerator == 0)
			return "0";

		if (this->base == 0)
			return "invalid number - devision by zero";

		if (this->base == 1)
			return std::to_string(this->numerator);

		if (isSimulated)
			return std::to_string(this->numerator) + "/" + std::to_string(this->base);

		std::string unSimulatedFraction = std::to_string(long long(this->numerator / this->base)) + "(" + std::to_string(abs(this->numerator % this->base)) + "/" + std::to_string(this->base) + ")";
		if (this->numerator % this->base == 0)
			return std::to_string(this->numerator) + "/" + std::to_string(this->base);
		if (unSimulatedFraction[0] == '0')
			return std::to_string(this->numerator) + "/" + std::to_string(this->base);
		return unSimulatedFraction;
	}

	fraction operator+(fraction number)
	{
		number.numerator = (this->numerator * number.base) + (this->base * number.numerator);
		number.base = this->base * number.base;
		number.reduce();
		return number;
	}

	void operator+=(fraction number)
	{
		this->numerator = (this->numerator * number.base) + (number.numerator * this->base);
		this->base = this->base * number.base;
		reduce();
	}

	fraction operator-(fraction number)
	{
		number.numerator = (this->numerator * number.base) - (this->base * number.numerator);
		number.base = this->base * number.base;
		number.reduce();
		return number;
	}

	void operator-=(fraction number)
	{
		this->numerator = (this->numerator * number.base) - (this->base * number.numerator);
		this->base = this->base * number.base;
		reduce();
	}

	fraction operator*(fraction number)
	{
		number.numerator = this->numerator * number.numerator;
		number.base = this->base * number.base;
		number.reduce();
		return number;
	}

	void operator*=(fraction number)
	{
		this->numerator = this->numerator * number.numerator;
		this->base = this->base * number.base;
		reduce();
	}

	fraction operator/(fraction number)
	{
		long long  tmpNumerator;
		long long  tmpBase;
		tmpNumerator = this->numerator * number.base;
		tmpBase = this->base * number.numerator;
		number.numerator = tmpNumerator;
		number.base = tmpBase;
		number.reduce();
		return number;
	}

	void operator/=(fraction number)
	{
		long long  tmpNumerator;
		long long  tmpBase;
		tmpNumerator = this->numerator * number.base;
		tmpBase = this->base * number.numerator;
		this->numerator = tmpNumerator;
		this->base = tmpBase;
		reduce();
	}

	fraction operator^(int exponentiation)
	{
		long double tmpNumerator = round(pow(this->numerator, exponentiation));
		long double tmpBase = round(pow(this->base, exponentiation));

		fraction f(tmpNumerator / tmpBase);
		return f;
	}

	bool operator>(fraction number)
	{
		if ((long double(this->numerator) / long double(this->base)) > (long double(number.numerator) / long double(number.base)))
			return true;
		return false;
	}

	bool operator>=(fraction number)
	{
		if ((long double(this->numerator) / long double(this->base)) >= (long double(number.numerator) / long double(number.base)))
			return true;
		return false;
	}

	bool operator<(fraction number)
	{
		if ((long double(this->numerator) / long double(this->base)) < (long double(number.numerator) / long double(number.base)))
			return true;
		return false;
	}

	bool operator<=(fraction number)
	{
		if ((long double(this->numerator) / long double(this->base)) <= (long double(number.numerator) / long double(number.base)))
			return true;
		return false;
	}

	void operator=(fraction number)
	{
		this->numerator = number.numerator;
		this->base = number.base;
	}

	void operator=(long long number)
	{
		this->numerator = number;
		this->base = 1;
	}

	void operator=(long double number)
	{
		fraction f(number);
		this->numerator = f.numerator;
		this->base = f.base;
	}

	bool operator==(fraction number)
	{
		if (long double(this->numerator) / long double(this->base) == long double(number.numerator) / long double(number.base))
			return true;
		return false;
	}

	bool operator!=(fraction number)
	{
		if (long double(this->numerator) / long double(this->base) != long double(number.numerator) / long double(number.base))
			return true;
		return false;
	}

};
