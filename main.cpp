#include <iostream>
#include <math.h>
#include <iomanip>

// prototypes for calculations
double calculateMonthlyLoanPayment();
double calculateInflation();
double calculateInterest();
double yearsToSavingsGoal();

// prototypes for user control
void displayHeader();
char checkUserChoice(char);
void executeUserChoice(char);
bool termBool();

int main() {
    displayHeader();
    return 0;
}

// functions
// displays menu option when asked and direct main framework for calculations

void displayHeader() {
    char choice;
    std::cout << "(M)onthly loan payment, (I)nflation calculator," << std::endl;
    std::cout << "(R)eal interest rate, (Y)ears to savings goal" << std::endl;
    std::cout << "Enter what you want to calculate: ";
    choice = checkUserChoice(choice);
    executeUserChoice(choice);
    // starts the loop over again whenever user wants to keep calculating payments
    while (termBool() == true)
    {
        displayHeader();
        break;
    }

}

char checkUserChoice(char choice)
{
    std::cin >> choice;
    if (choice == 'm' || choice == 'M')
    {
        choice = 'M';
    }
    if (choice == 'i' || choice == 'I')
    {
        choice = 'I';
    }
    if (choice == 'r' || choice == 'R')
    {
        choice = 'R';
    }
    if (choice == 'y' || choice == 'Y')
    {
        choice = 'Y';
    }
    return choice;
}

void executeUserChoice(char choice)
{
    if (choice == 'm' || choice == 'M')
    {
        calculateMonthlyLoanPayment();
    }
    if (choice == 'i' || choice == 'I')
    {
        calculateInflation();
    }
    if (choice == 'r' || choice == 'R')
    {
        calculateInterest();
    }
    if (choice == 'y' || choice == 'Y')
    {
        yearsToSavingsGoal();
    }
}

bool termBool() {
    char token;
    bool truthToken;
    std::cout << "Do you want to do another calculation [y/n]? ";
    std::cin >> token;
    if (token == 'y' || token == 'Y')
        {
        return true;
        }
    else
        {
        return false;
        }

}
double calculateMonthlyLoanPayment()
{
    double principal;
    int term;
    double interestRate;
    double monthlyPayment;
    double discountFactor;

    // given annual terms and rates, must convert to monthly
    double monthlyInterestRate;
    double monthlyTerm;

    std::cout << "Enter principal: ";
    std::cin >> principal;
    std::cout << "Enter term (years): ";
    std::cin >> term;
    monthlyTerm = static_cast<float>(term) * 12;

    std::cout << "Enter annual interest rate: ";
    std::cin >> interestRate;
    if (interestRate == 0.0)
    {
        monthlyPayment = principal / (12 * term);
        std::cout << std::fixed << std::setprecision(2) << "Your monthly payment is $" << monthlyPayment << "." << std::endl;
        return 0;
    }
    monthlyInterestRate = interestRate / 12;


    // calculations for monthly loan payment
    // P = A / D
    // P = payment amount, A = principal, D = discount factor
    // https://www.thebalance.com/loan-payment-calculations-315564

    // must use correct parenthesis in calculations with pow
    discountFactor = ((pow (monthlyInterestRate + 1.0, monthlyTerm) - 1.0 )/ (pow (monthlyInterestRate + 1.0, monthlyTerm) * monthlyInterestRate));
    monthlyPayment = principal / discountFactor;
    std::cout << std::fixed << std::setprecision(2) << "Your monthly payment is $" << monthlyPayment << "." << std::endl;
    return monthlyPayment;
}
double calculateInflation()
{
    int startYear;
    double oldDollars;
    int endYear;
    double inflationRate;
    double currentDollars;
    int numYears;

    std::cout << "Enter the starting year: ";
    std::cin >> startYear;
    std::cout << "Enter the amount of " << startYear << " dollars: ";
    std::cin >> oldDollars;
    std::cout << "Enter the ending year: ";
    std::cin >> endYear;
    std::cout << "Enter the inflation rate: ";
    std::cin >> inflationRate;
    // perform calculations
    // formula found on https://www.omnicalculator.com/finance/inflation
    // computes final price from initial * inflation ^ years
    numYears = endYear - startYear;
    currentDollars = pow(inflationRate + 1.0, static_cast<double>(numYears)) * oldDollars;
    std::cout << std::fixed << std::setprecision(2) << "$" << oldDollars << " in " << startYear << " has the same value as $"
    << currentDollars << " in " << endYear << "." << std::endl;
    return currentDollars;
}

double calculateInterest()
{
    double nominalInterest;
    double inflationRate;
    double realInterestRate;

    std::cout << "Enter the nominal interest rate: ";
    std::cin >> nominalInterest;
    std::cout << "Enter the inflation rate: ";
    std::cin >> inflationRate;

    // calculations for finding the real interest rate.
    realInterestRate = (nominalInterest - inflationRate) / (1 + inflationRate);
    std::cout << std::fixed << std::setprecision(2) << "The real interest rate is " << realInterestRate << "." << std::endl;

    return realInterestRate;
}
double yearsToSavingsGoal()
{
    double savingsGoal;
    double currentSavings;
    double monthlyContribution;
    double interestRate;
    double years;

    std::cout << "Enter savings goal: ";
    std::cin >> savingsGoal;
    std::cout << "Enter current savings: ";
    std::cin >> currentSavings;
    std::cout << "Enter monthly contribution: ";
    std::cin >> monthlyContribution;
    std::cout << "Enter annual interest rate: ";
    std::cin >> interestRate;
    if (interestRate == 0)
    {
        years = (savingsGoal - currentSavings) / (12 * monthlyContribution);
        std::cout << std::fixed << std::setprecision(2) << "The savings goal of $" << savingsGoal << " will be reached in "
                  << years << " years." << std::endl;
        return 0;
    }

    // formula to calculate the years to accumulate money for savings goal
    years = log ((interestRate * savingsGoal + 12 * monthlyContribution + monthlyContribution * interestRate) / (currentSavings * interestRate + 12 * monthlyContribution + monthlyContribution * interestRate)) / (12 * log (1 + interestRate / 12));
    std::cout << std::fixed << std::setprecision(2) << "The savings goal of $" << savingsGoal << " will be reached in "
              << years << " years." << std::endl;


    return years;
}
