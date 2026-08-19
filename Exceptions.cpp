// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <string>

// Custom exception class derived from std::exception.
// This allows us to create application-specific exceptions.
class CustomException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "A custom application exception occurred.";
    }
};

bool do_even_more_custom_application_logic()
{
    // Throw a standard exception to simulate an application error.
    throw std::runtime_error("An error occurred in Even More Custom Application Logic.");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    // Wrap the function call in a try block so standard exceptions
    // can be caught and handled without terminating the program.
    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& ex)
    {
        // Display the exception message and continue processing.
        std::cout << "Standard Exception Caught: " << ex.what() << std::endl;
    }

    // Throw a custom exception that will be caught explicitly in main.
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den)
{
    // Prevent divide-by-zero by throwing a standard exception.
    if (den == 0.0f)
    {
        throw std::runtime_error("Cannot divide by zero.");
    }

    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0.0f;

    // Catch only the exception type thrown by divide().
    try
    {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator
                  << ") = " << result << std::endl;
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << "Division Error: " << ex.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // Wrap the entire application so all exceptions are handled gracefully.
    try
    {
        do_division();
        do_custom_application_logic();
    }
    // Catch the custom exception first since it derives from std::exception.
    catch (const CustomException& ex)
    {
        std::cout << "Custom Exception Caught: " << ex.what() << std::endl;
    }
    // Catch any remaining standard exceptions.
    catch (const std::exception& ex)
    {
        std::cout << "Standard Exception Caught in main: " << ex.what() << std::endl;
    }
    // Catch any unexpected exceptions not derived from std::exception.
    catch (...)
    {
        std::cout << "An unknown exception occurred." << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu