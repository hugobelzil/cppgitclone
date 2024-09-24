# cppgitclone (EnhancedGIT)
A file-versioning system in C++ made as an assignment of the course COMP322 (Introduction to C++) at McGill University.
This code was written in March 2023, and has not been modified since.
Thanks to Dr. Chad Zammar for allowing me to share my code.

### Overview:
This project is a C++ implementation that focuses on version control using object-oriented design principles. The program extends a previous versioning tool (previous assignment in this class, which consisted of writing the `Git322` class) by incorporating class-based structure and persistence features.

### Features:

1. **Git322 Class**  
   The `Git322` class serves as the core of the versioning system, implementing all version control functionality. It includes:
   - Public methods for versioning operations (add, delete, search versions).
   - A linked list structure for storing file versions, handled by the `LinkedList` class.

2. **LinkedList Class**  
   This class manages the linked list structure used by `Git322` to store and retrieve file versions. It includes:
   - Methods for adding, deleting, and searching versions.

3. **EnhancedGit322 Class**  
   Inherits from `Git322` and adds persistence functionality. It allows the program to:
   - Save version data between runs.
   - Load saved versions automatically on restart, ensuring continuity.

### Code Structure:
- All functionality from the previous version has been refactored into object-oriented design.
- The main function has been adapted to test and demonstrate both `Git322` and `EnhancedGit322` features.

