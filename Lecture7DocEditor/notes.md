C++ OOP & LLD Core Mechanics: Study Notes
Here is a consolidated cheat sheet of the C++ class design principles we covered. These concepts are fundamental for writing robust, memory-safe backend systems and passing Low-Level Design interviews.

1. const Member Functions
Purpose: Guarantees a function will not modify the object's state (read-only).

Mechanism: Locks the hidden this pointer as const, making all member variables temporarily read-only.

Why it matters:

Allows objects to be passed efficiently via const & without compiler errors.

For abstract base classes, the const qualifier is part of the strict signature. Derived classes must include it to successfully override the virtual function.

2. The mutable Keyword
Purpose: An exception to the const rule. Allows specific member variables to be modified inside a const function.

Use Cases: Differentiates between logical state (what the user sees) and physical state (under the hood). Commonly used for caching, invocation counters, or locking a std::mutex for thread safety without breaking the const contract of the function.

3. virtual Destructors
Purpose: Prevents memory leaks during polymorphism.

The Trap: If you delete a derived object (like TextElement) using a base class pointer (DocumentElement*), a non-virtual base destructor will only destroy the base class, leaking the derived class's memory.

The Fix: Adding virtual forces the compiler to resolve the true object type at runtime, ensuring ~TextElement() is called before ~DocumentElement().

Syntax: virtual ~DocumentElement() = default; generates the standard empty destructor while keeping the crucial virtual tag.

4. Member Initializer Lists vs. Assignment
Purpose: Optimal variable initialization in constructors.

The Two-Step Penalty: Writing this->text = text; inside the constructor body forces the compiler to first create an empty string (step 1), and then overwrite it (step 2).

The Solution: Using the initializer list (: text(text)) constructs the variable directly with the data, completing the operation in exactly one step.

5. std::move in Constructors
Purpose: Eliminates expensive memory copies.

Mechanism: Instead of allocating new memory and copying a passed-in string byte-by-byte, std::move(text) tells the compiler to steal the memory pointer from the soon-to-be-destroyed local parameter and hand it directly to the class member.

6. The explicit Keyword
Purpose: Disables automatic, silent type conversions for single-argument constructors.

The Bug: Without it, passing a raw string to a function expecting a TextElement allows the compiler to secretly build a temporary TextElement object, hiding logic errors.

The Fix: Marking the constructor explicit forces the developer to manually invoke the constructor (e.g., TextElement("data")), keeping memory allocations intentional and predictable.

These rules collectively enforce strict boundaries in C++, ensuring that as an application scales, memory is managed predictably and state modifications remain intentional.