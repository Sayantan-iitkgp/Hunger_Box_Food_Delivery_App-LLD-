# HungerBox Food Delivery App LLD

## Overview
HungerBox is a C++ Low-Level Design (LLD) project that models the core backend architecture of a food delivery platform, similar to Zomato or Swiggy. The system demonstrates strong Object-Oriented Programming (OOP) principles, SOLID design, and the use of classic design patterns (Strategy, Factory, Singleton) to ensure extensibility, maintainability, and clarity.

---

## Architecture Diagram

```
+-------------------+         +-------------------+         +-------------------+
|   User            |         |   HotelManager    |         | NotificationService|
+-------------------+         +-------------------+         +-------------------+
| - userId          |         | - hotelsByLoc     |         | - notificationBox |
| - cart            |         |                   |         |                   |
| - orderHistory    |         |                   |         |                   |
+-------------------+         +-------------------+         +-------------------+
        |                              |                              |
        |                              |                              |
        v                              v                              v
+-------------------+         +-------------------+         +-------------------+
|   Cart            |         |   Hotel           |         | OrderService      |
+-------------------+         +-------------------+         +-------------------+
| - items           |         | - menuItems       |         | - orderBoxes      |
+-------------------+         +-------------------+         +-------------------+
        |                              |                              |
        v                              v                              v
+-------------------+         +-------------------+         +-------------------+
|   IOrder (abstract)|<--------| OrderPaymentFactory|------->| Ipayment (abstract)|
+-------------------+         +-------------------+         +-------------------+
| - paymentStrategy |         | (Singleton)       |         |                   |
| - orderType       |         |                   |         |                   |
+-------------------+         +-------------------+         +-------------------+
        |                              |                              |
        |------------------------------|------------------------------|
        v                              v                              v
+-------------------+         +-------------------+         +-------------------+
| HomeDelivery      |         | PickUp            |         | UPI/NetBanking/   |
+-------------------+         +-------------------+         | CashOnDelivery    |
                                                        +-------------------+
```

---

## Key Components & Patterns

### 1. Models
- **User**: Represents a customer, holds a cart and order history.
- **Cart**: Stores items the user wants to order.
- **Hotel**: Represents a restaurant, contains menu items.
- **Menu_Item**: Represents a food item.
- **OrderBox**: Tracks active and completed orders for a user.
- **Notification_Box**: Stores notifications for a user.

### 2. Services & Managers (Singletons)
- **HotelManager (Singleton)**: Only one instance exists; manages all hotels and their menus.
- **OrderService (Singleton)**: Only one instance exists; handles order placement, order history, and active orders.
- **NotificationService (Singleton)**: Only one instance exists; sends and stores notifications for users.

### 3. Strategy Pattern
- **IOrder**: Abstract base for order types (e.g., HomeDelivery, PickUp).
- **Ipayment**: Abstract base for payment types (e.g., UPI, NetBanking, CashOnDelivery).
- **Concrete Strategies**: Implement different order and payment behaviors.

### 4. Factory Pattern
- **OrderPaymentFactory (Singleton)**: Centralized creation of order and payment strategy objects based on user choice. Only one instance exists.

---

## SOLID & OOP Principles
- **Single Responsibility**: Each class has a focused responsibility (e.g., Cart only manages cart items).
- **Open/Closed**: New order/payment types can be added without modifying existing code.
- **Liskov Substitution**: Derived strategies can be used wherever base pointers are expected.
- **Interface Segregation**: Abstract interfaces are focused and not overly broad.
- **Dependency Inversion**: High-level modules depend on abstractions, not concrete classes.
- **Singleton Pattern**: HotelManager, NotificationService, OrderService, and OrderPaymentFactory are all implemented as singletons to ensure a single point of management for their respective domains.
- **Encapsulation, Inheritance, Polymorphism, Abstraction**: All core OOP principles are demonstrated.

---

## Example Flow
1. **User Registration**: User is created and registered with NotificationService and OrderService.
2. **Hotel/Menu Setup**: Hotels and menu items are added via HotelManager.
3. **Cart Operations**: User adds/removes items from their cart.
4. **Order Placement**: User places an order; OrderPaymentFactory creates the correct order and payment strategy.
5. **Payment Processing**: Payment strategy processes the payment and notifies the user.
6. **Order History & Notifications**: User can view order history and notifications.

---

## Extensibility
- Add new payment/order types by subclassing `Ipayment`/`IOrder` and updating the factory.
- Add new services or features (e.g., ratings, discounts) by following the same modular approach.

---

## How to Run
1. Build with any C++17+ compiler (e.g., g++):
   ```sh
   g++ -Wall -Wextra -g3 Main.cpp -o output/Main.exe
   ```
2. Run the executable:
   ```sh
   ./output/Main.exe
   ```

---

## Why Include in Your CV?
- Demonstrates real-world LLD, OOP, and design pattern skills.
- Shows ability to design extensible, maintainable backend systems.
- Good for interviews and as a portfolio project.

---

## Author
- [Your Name]
- [Your Email/LinkedIn]
