#include <iostream>
#include <string>

/*
 * OOP Concept: Abstraction & Interface
 * - The "Product" class defines a pure virtual function Operation().
 * - This makes Product an abstract class that serves as an interface
 *   that all concrete product classes must implement.
 */
class Product
{
public:
    virtual ~Product() {}
    // Pure virtual function: all products must provide their own implementation.
    virtual std::string Operation() const = 0;
};

/*
 * Concrete Products: Implement the Product interface.
 * OOP Concepts:
 * - Inheritance: Both ConcreteProduct1 and ConcreteProduct2 derive from Product.
 * - Polymorphism: They provide different implementations of Operation(), which
 *   allows the client code to use them interchangeably via the Product interface.
 */
class ConcreteProduct1 : public Product
{
public:
    std::string Operation() const override
    {
        return "ConcreteProduct1";
    }
};

class ConcreteProduct2 : public Product
{
public:
    std::string Operation() const override
    {
        return "ConcreteProduct2";
    }
};

/*
 * Creator (Factory):
 * - Abstract class that declares the FactoryMethod.
 * - This abstract method is used to create Product objects.
 * OOP Concepts:
 * - Abstraction: Creator is abstract because it has a pure virtual function.
 * - Encapsulation: It encapsulates the product creation logic from the client.
 */
class Creator
{
public:
    virtual ~Creator() {}
    // Pure virtual factory method to be overridden by concrete creators.
    virtual Product *FactoryMethod() const = 0;

    /*
     * SomeOperation: Demonstrates the use of the Product.
     * - It calls the factory method to get a product and then uses it.
     * - This shows how the client code is decoupled from the concrete product classes.
     */
    std::string SomeOperation() const
    {
        Product *product = FactoryMethod();
        std::string result = "Creator: Working with " + product->Operation();
        delete product; // Prevent memory leak by deleting the created product.
        return result;
    }
};

/*
 * Concrete Creators:
 * - These classes override the FactoryMethod to create specific concrete products.
 * OOP Concepts:
 * - Inheritance: They derive from the Creator base class.
 * - Polymorphism: Client code can use any ConcreteCreator interchangeably.
 */
class ConcreteCreator1 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct2();
    }
};

/*
 * Client Code:
 * - Works with the Creator interface to perform operations.
 * - The client is unaware of which concrete product it gets, demonstrating loose coupling.
 */
void ClientCode(const Creator &creator)
{
    std::cout << creator.SomeOperation() << std::endl;
}

/*
 * Main Function:
 * - Demonstrates the Factory Design Pattern by creating different ConcreteCreators.
 * - The client code calls SomeOperation() without needing to know the details of product creation.
 */
int main()
{
    ConcreteCreator1 creator1;
    ConcreteCreator2 creator2;

    ClientCode(creator1);
    ClientCode(creator2);

    return 0;
}
