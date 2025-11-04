# COS 214 Final Project
# GreenHome💚🏕️🌿🌲🌳☘️
**Welcome to GreenHome. Where plants meet innovation and care.**

This project simulates a smart greenhouse system that integrates what we have learnt in COS 214 to manage plants, staff, and customer interactions efficiently.

<img width="1024" height="585" alt="nursery" src="https://github.com/user-attachments/assets/40046efb-c91c-4903-9c34-742fb5c6fccf" />

# Meet the team 𐦂𖨆𐀪𖠋𐀪𐀪
---
|Name|Main Design Patterns Implemented|
|------|-----------------------------------------|
|Brayden Butler| Factory Method, Decorator, Prototype, Composite|
|Mosa Leiee| Iterator, State, Strategy|
|Sente Mngomezulu| Mediator, chain of responsibility|
|Kundai Ndemera| Singleton, Observer|
|Lesedi Padi| Command, Builder|
---

# System Overview🦜
The system begins by initializing the Greenhouse, which serves as the central hub for 
plant management and staff coordination. The inventory is attached to the Greenhouse 
as an observer to track all plant additions and removals. The program also sets up 3 
plant factories —Flower, Succulent, and Tree —each responsible for creating its 
respective plant type using the Factory Method Pattern. 
The builder pattern and Command pattern are then initialized to handle various actions 
in the system, such as selling plants, watering plants, and providing sunlight. These 
commands are later linked to the appropriate staff members. 
Initially, a few sample plants (rose, oak, cactus, tulip) are created and added to the 
Greenhouse. 

# Staff Roles
- **Manager**- oversees all operations, handles plant care requests, and coordinates 
between staff. 
- **Salesclerk**- interacts with customers and executes the sell plant command. 
- **Ground Staff**- responsible for watering and sunlight care, using the respective 
commands. 
Each staff member is linked via the chain of responsibility pattern, allowing unhandled 
requests to be passed along the chain. 

---
# User Interaction

## Customer Mode👩

• Provide their name and it is added to both the HelpDesk and SalesRoom 
sections. 
• The customer can view all plants currently in the greenhouse; purchase plants or 
ask for help via the help desk. 
• Each customer action creates and sends a request message (e.g., purchase or 
help) to the corresponding staff section. 
• The Salesclerk or Manager processes the request through the mediator system. 

## Staff Mode👷

- The user must enter a password to access staff functionalities. 
- Once authenticated, the staff can care for plants, add plants to the greenhouse, 
remove plants, view existing plants, and access section history to review Help 
desk and sales room activity logs. 
- All plant additions and removals trigger observer notifications to the Inventory, 
ensuring consistency. 
When the user finishes, the system detaches the Inventory observer, removes all 
dynamically allocated entities (plants, staff, sections, command, etc.) and exists. 
---

# How to compile and Run⌨️
- make clean: cleans the .o files
- make all: cleans and compiles all files on the repo.
- make run: runs the files
Follow the steps to be able to use our program/system.

# How to run unit/integrated testing⌨️
- make tests

# Link to Report
https://docs.google.com/document/d/1BdWMNZtlrCkOYYhAnO_Sj27GYvwT37ylevLtTDNC_Z8/edit?usp=sharing

# Closing Note🌿
Greenhouse represents a modern, pattern-driven approach to software design- where collaboration, maintainability, and resusability


