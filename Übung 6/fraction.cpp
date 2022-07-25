#include <cassert>
#include <iostream>

class Fraction{
	private:

	int z_;
	int n_;

	public:

	Fraction(int z, int n){
		z_ = z;
		if (n == 0) {
			throw std::invalid_argument("Nenner eines Bruchs darf nicht 0 sein.");
		}
		n_ = n;
	}
	Fraction(int z){
		z_ = z;
		n_ = 1;
	}

	friend std::ostream& operator<< (std::ostream& os,Fraction frac);

	void reduce(Fraction& frac){
		if (frac.n_ == 0) {
			throw std::invalid_argument("Nenner eines Bruchs darf nicht 0 sein.");
		}
		if (frac.z_ == 0 || frac.n_ == 1){
			frac.n_ = 1;
			return;
		}
		bool neg = false;
		int small, large;
		if (frac.n_ < 0 != frac.z_ < 0){
			neg = true;
		}
		frac.n_ = std::abs(frac.n_);
		frac.z_ = std::abs(frac.z_);
		if(frac.n_ < frac.z_){
			small = frac.n_; large = frac.z_;
		}
		else{
			small = frac.z_; large = frac.n_;
		}
		while(small != large){
			large = large - small;
			if(large < small){
				small += large;
				large = small - large;
				small -= large;
			}
		}
		frac.n_ /= large;
		frac.z_ /= large;
		if (neg) frac.z_ *= -1;
	}
	Fraction add(Fraction frac2){
		Fraction result = Fraction(this->z_*frac2.n_+this->n_*frac2.z_,this->n_*frac2.n_);
		result.reduce(result);
		return result;
	}
	Fraction subtract(Fraction frac2){
		Fraction result = Fraction(this->z_*frac2.n_-this->n_*frac2.z_,this->n_*frac2.n_);
		result.reduce(result);
		return result;
	}
	Fraction multiply(Fraction frac2){
		Fraction result = Fraction(this->z_*frac2.z_,this->n_*frac2.n_);
		result.reduce(result);
		return result;
	}
	Fraction divide(Fraction frac2){
		assert(frac2.z_!=0);
		Fraction result = Fraction(this->z_*frac2.n_,this->n_*frac2.z_);
		result.reduce(result);
		return result;
	}

	operator double() const{
		double z = static_cast<double>(z_);
		double n = static_cast<double>(n_);

		return z/n;
	}

};

std::ostream& operator<<(std::ostream& os,Fraction frac){
	frac.reduce(frac);
	if (frac.z_< 0) {
		os << "-";
	}else if (frac.z_ == 0){
		os << 0;
		return os;
	}
	if ((std::abs(frac.z_)%std::abs(frac.n_))== 0) {
		os << (std::abs(frac.z_)/(std::abs(frac.n_)));
	} else if(std::abs(frac.z_) < std::abs(frac.n_)) {
		os << frac.z_ << "/" << frac.n_;
	} else {
		os << (std::abs(frac.z_)/(std::abs(frac.n_))) << " " << (std::abs(frac.z_)%(std::abs(frac.n_))) << "/" << std::abs(frac.n_);
	}
	
	return os;
}

Fraction operator+(Fraction frac1, Fraction frac2){ return frac1.add(frac2);}
Fraction operator+(int i, Fraction frac){return Fraction(i).add(frac);}
Fraction operator+(Fraction frac, int i){return Fraction(i).add(frac);}

Fraction operator-(Fraction frac1, Fraction frac2){ return frac1.subtract(frac2);}
Fraction operator-(Fraction frac, int i){return frac.subtract(Fraction(i));}
Fraction operator-(int i, Fraction frac){return Fraction(i).subtract(frac);}

Fraction operator*(Fraction frac1, Fraction frac2){ return frac1.multiply(frac2);}
Fraction operator*(int i, Fraction frac){return Fraction(i).multiply(frac);}
Fraction operator*(Fraction frac, int i){return Fraction(i).multiply(frac);}

Fraction operator/(Fraction frac1, Fraction frac2){ return frac1.divide(frac2);}
Fraction operator/(Fraction frac, int i){return frac.divide(Fraction(i));}
Fraction operator/(int i, Fraction frac){return Fraction(i).divide(frac);}

void runTests()
{
	/*Die folgenden drei Zeilen sind selbst eingefügt.*/
	std::cout << Fraction(2,3) << std::endl; // Should print "2/3"
	std::cout << Fraction(5,4) << std::endl; // Should print "1 1/4"
	std::cout << Fraction(9,3) << std::endl; // Should print "3"
	/* Test exception */
	try{
		std::cout << Fraction(4, 0);
		assert(false);
	} catch (const std::invalid_argument&) {
		std::cout << "Invalid input." << std::endl;
	}
	std::cout << Fraction(2, 3) - Fraction(2, 3) << '\n'; // Should print 0 and not throw an exception

	/* Store values instead of generating them inline to better test the method's signature */
	 const Fraction fraction_4_5(4, 5);
	 const Fraction fraction_1_3(1, 3);

	/* Some simple test cases for operator overloading of fractions */
	std::cout << fraction_4_5 + Fraction(2, 4) << '\n'; // Should print "1 3/10"
	std::cout << fraction_4_5 - Fraction(2, 4) << '\n'; // Should print "3/10"
	std::cout << fraction_1_3 * Fraction(2, 4) << '\n'; // Should print "1/6"
	std::cout << fraction_1_3 / Fraction(2, 4) << '\n'; // Should print "2/3"

	/* Some simple test cases for operator overloading of fractions in connection with integers */
	std::cout << fraction_4_5 + 2 << '\n'; // Should print "2 4/5"
	std::cout << fraction_4_5 - 2 << '\n'; // Should print "-1 1/5"
	std::cout << fraction_1_3 * 3 << '\n'; // Should print "1"
	std::cout << fraction_1_3 / 3 << '\n'; // Should print "1/9"

	/* Test global operator functions */
	std::cout << 2 + fraction_4_5 << '\n'; // Should print "2 4/5"
	std::cout << 2 - fraction_4_5 << '\n'; // Should print "1 1/5"
	std::cout << -3 * fraction_1_3 << '\n'; // Should print "-1"
	std::cout << -3 / fraction_1_3 << '\n'; // Should print "-9"

	/* Test constexpr (ZA2)*/
	//constexpr Fraction constexprFrac = -1 * ((Fraction(4, 5) / 2 + Fraction(2, 4) * (Fraction(3, 9) - 1)) * 3 + 4 - Fraction(1, 5)) / Fraction(7, 2);
	//std::cout << constexprFrac << '\n'; // Should print "-1 1/7"

	/* Test User - defined conversion function (ZA1)*/
	double castedValue = static_cast<double>(Fraction(3, 4));
	std::cout << castedValue << '\n'; // Should print 0.75
}

int main()
{
	try
	{
		runTests();
	}
	catch (const std::invalid_argument&)
	{
		return 1;
	}

	return 0;
}
