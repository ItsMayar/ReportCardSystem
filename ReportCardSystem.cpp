#include "ReportCardSystem.h"

const std::string ReportCardSystem::_STUDENT_FILE = "student_data.bin";

// Main menu of program
void ReportCardSystem::mainMenu()
{
    char choice = -100;
    bool exit = false;
    do
    {
        Util::clear();
        std::cout << "\n\n\n\t\t      Student Report Card System"
            << "\n\t\t====================================="
            << "\n\t\t|    (1) Add Student                |"
            << "\n\t\t|    (2) Add Subject                |"
            << "\n\t\t|    (3) Edit Student               |"
            << "\n\t\t|    (4) Edit Subject               |"
            << "\n\t\t|    (5) Remove Student             |"
            << "\n\t\t|    (6) Remove Subject             |"
            << "\n\t\t|    (7) Search Student             |"
            << "\n\t\t|    (8) Export Students to File    |"
            << "\n\t\t|    (9) Save All                   |"
            << "\n\t\t|    (0) Exit (Auto save)           |"
            << "\n\t\t=====================================";
        if (choice == -1)
            std::cout << "\n\t\tInvalid Choice!";
        choice = menu_prompt('0', '9');
        Util::clear();
        switch(choice)
        {
            case '1':
                addStud();
                break;

            case '2':
                addSub();
                break;

            case '3':
                editStud();
                break;

            case '4':
                editSub();
                break;

            case '5':
                removeStud();
                break;

            case '6':
                removeSub();
                break;

            case '7':
                searchStud();
                break;
            
            case '8':
                printStudMul();
                break;

            case '9':
                write_file(_STUDENT_FILE);
                break;
            
            case 'p':
                printVec();
                break;

            case '0':
                exit = exit_internal();
                break;

            default:
                break;
        }
        if (choice > '0')
            Util::pause();
    } while (!exit);
}

// Adds student to vector
void ReportCardSystem::addStud()
{
    Student s;

    std::string sid, fname, lname, fac;
    
    bool bsid, bfname, blname, bfac;
    bool addLoop = true;
    bool intError = false;
    
    int id;
    int bsidSearch;
    
    char inputConfirm;

    // Enter student information
    std::cout << "\n\t----- Add Student -----\n\n";
    do
    {
        std::cout << "Student ID (0 to cancel): ";
        std::getline(std::cin, sid);
        intError = false;
        try
        {
            id = stoi(sid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid ID! (10 digits)\n\n";
            intError = true;
        }

        if (!intError)
        {
            if (id == 0)
            {
                std::cout << "Cancelled adding student\n\n";
                return;
            }
            bsidSearch = search(id);
            if (bsidSearch != -1)
                std::cout << "Student already exist!\n\n";
            bsid = s.setID(id);
        }

    // If adding stud id fails or, 
    // if already has student, repeat
    } while (!bsid || bsidSearch != -1);

    do
    {
        std::cout << "Student first name\t: ";
        std::getline(std::cin, fname);
        bfname = s.setFirstName(fname);
    
    // If adding first name fails, repeat
    } while (!bfname);

    do
    {
        std::cout << "Student last name\t: ";
        std::getline(std::cin, lname);
        blname = s.setLastName(lname);
    
    // If adding last name fails, repeat
    } while (!blname);

    do
    {
        std::cout << "Student faculty\t\t: ";
        std::getline(std::cin, fac);
        std::cout << "\n";
        bfac = s.setFaculty(fac);
    
    // If adding faculty fails, repeat
    } while (!bfac);

    // Print student info
    s.printInfo();

    // Ask confirmation to add
    do
    {
        std::cout << "Add this student? (Y/N): ";
        std::cin >> inputConfirm;
        std::cin.ignore();
        inputConfirm = tolower(inputConfirm);
        
        // Check user input
        switch (inputConfirm)
        {
        case 'y':
            vec.push_back(s);
            std::cout << "Student successfully added!\n\n";
            sort();
            return;

        case 'n':
            std::cout << "Student not added!\n\n";
            return;
        
        default:
            std::cout << "Invalid choice!\n\n";
            addLoop = true;
        }
    } while (addLoop);
}

// Adds subject to a student in the vector
void ReportCardSystem::addSub()
{
    Student s;
    ReportEntry r;
    
    std::string sid, subname, subscore;
    int id;
    double doubleSubScore;

    bool bsubname, bsubscore;
    bool addLoop;
    bool intError, doubleError;
    bool edited = false;
    
    int studIndex = -1;
    
    char inputConfirm;

    // Ask for student id to search
    std::cout << "\n\t----- Add Subject -----\n\n";
    do
    {
        std::cout << "Enter Student ID (0 to cancel): ";
        std::getline(std::cin, sid);
        intError = false;
        try
        {
            id = stoi(sid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid ID! (10 digits)\n\n";
            intError = true;
        }

        if (!intError)
        {
            if (id == 0)
            {
                std::cout << "Cancelled adding subject\n\n";
                return;
            }
            studIndex = search(id);
            if (studIndex == -1)
                std::cout << "Student not found!\n\n";
        }
    
    // If student not found, repeat
    } while (studIndex == -1);

    s = vec[studIndex];
    s.printInfo();

    // If user wants to add more subjects
    bool addMoreSub;
    // Number of subjects student currently has
    int subCount;
    // Ask user for subject info
    do
    {
        // Update subCount every time user wants to add more
        subCount = s.getSubjectCount();
        
        // Checks subCount exceeds subject limit
        if (++subCount > s.getMaxEntries())
        {
            std::cout << "Max subjects reached!\n\n";
            break;
        }

        // Ask for subject name to add
        std::cout << "\n--- Add Subject " << subCount << " ---\n";
        do
        {
            bsubname = false;
            std::cout << "Name : ";
            std::getline(std::cin, subname);
            bsubname = r.setName(subname);
            subname.clear();
        } while (!bsubname);

        // Ask for subject score to add
        do
        {
            bsubscore = false;
            std::cout << "Score: ";
            std::getline(std::cin, subscore);
            doubleError = false;
            try
            {
                doubleSubScore = std::stod(subscore);
            }
            catch (std::exception)
            {
                std::cout << "Invalid Subject Score!\n\n";
                doubleError = true;
            }

            if (!doubleError)
                bsubscore = r.setScore(doubleSubScore);
            subscore.clear();
            doubleSubScore = 0;
        } while (!bsubscore);
        
        // Print report entry
        r.printEntry();

        // Ask for confirmation
        do
        {
            std::cout << "\nAdd this subject? (Y/N): ";
            std::cin >> inputConfirm;
            std::cin.ignore();
            inputConfirm = tolower(inputConfirm);
            
            switch (inputConfirm)
            {
            case 'y':
                s.addReportEntry(r);
                addLoop = false;
                edited = true;
                break;

            case 'n':
                std::cout << "Subject not added!\n\n";
                addLoop = false;
                break;
            
            default:
                std::cout << "Invalid choice!\n\n";
                addLoop = true;
            }
        } while (addLoop);

        // Ask to add more subjects
        do
        {
            std::cout << "Add more subjects? (Y/N): ";
            std::cin >> inputConfirm;
            std::cin.ignore();
            inputConfirm = tolower(inputConfirm);
            
            switch (inputConfirm)
            {
            case 'y':
                addMoreSub = true;
                addLoop = false;
                break;

            case 'n':
                subCount = s.getMaxEntries();
                addMoreSub = false;
                addLoop = false;
                break;
            
            default:
                std::cout << "Invalid choice!\n\n";
                addLoop = true;
            }
        } while (addLoop);
        // std::cout << "\nsubCount: " << subCount << "\n";
    } while (addMoreSub);

    if (edited)
    {
        s.printInfo();
        do
        {
            std::cout << "Save changes? (Y/N): ";
            std::cin >> inputConfirm;
            std::cin.ignore();
            inputConfirm = tolower(inputConfirm);
            
            switch (inputConfirm)
            {
            case 'y':
                vec[studIndex] = s;
                std::cout << "Changes successfully saved!\n\n";
                addLoop = false;
                break;

            case 'n':
                std::cout << "Changes not saved!\n\n";
                addLoop = false;
                break;
            
            default:
                std::cout << "Invalid choice!\n\n";
                addLoop = true;
            }
        } while (addLoop);
    }
    else
        std::cout << "No changes made, returning...\n\n";
}

// Edit student in the vector
void ReportCardSystem::editStud()
{
    Student s;

    std::string sid, fname, lname, fac;
    bool bsid, bfname, blname, bfac;

    bool addLoop = true;
    bool intError;
    bool edited = false;

    int id, studIndex;

    char inputConfirm;

    // Search student
    std::cout << "\n\t----- Edit Student -----\n\n";
    do
    {
        std::cout << "Enter Student ID to edit (0 to cancel): ";
        std::getline(std::cin, sid);
        intError = false;
        try
        {
            id = stoi(sid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid ID! (10 digits)\n\n";
            intError = true;
        }

        if (!intError)
        {
            if (id == 0)
            {
                std::cout << "Cancelled editing student\n\n";
                return;
            }
            studIndex = search(id);
            if(studIndex == -1)
                std::cout << "Student not found!\n\n";
        }
    } while(studIndex == -1);

    // s is a pointer because we need to directly edit the student in the vector
    s = vec[studIndex];
    s.printDetails();

    std::cout << "\n\t----- Editing Student -----\n\n";
    // Edit student id (if non empty)
    do
    {
        std::cout << "Student ID\t\t: ";
        std::getline(std::cin, sid);
        intError = false;
        if (!sid.empty())
        {
            try
            {
                id = stoi(sid);
            }
            catch (std::exception)
            {
                std::cout << "Invalid ID! (10 digits)\n\n";
                intError = true;
            }
        }
        else
            break;

        if (!intError)
        {
            if (id != 0)
            {
                bsid = s.setID(id);
                if (bsid)
                    edited = true;
            }
            else
                bsid = true;
        }
    } while (intError || !bsid);

    // Edit student first name (if non empty)
    do
    {
        std::cout << "Student first name\t: ";
        std::getline(std::cin, fname);
        if (!fname.empty())
        {
            bfname = s.setFirstName(fname);
            if (bfname)
                edited = true;
        }
        else
            break;
    } while (!bfname);

    // Edit student last name (if non empty)
    do
    {
        std::cout << "Student last name\t: ";
        std::getline(std::cin, lname);
        if(!lname.empty())
        {
            blname = s.setLastName(lname);
            if (blname)
                edited = true;
        }
        else
            break;
    } while (!blname);

    // Edit student faculty (if non empty)
    do
    {
        std::cout << "Student faculty\t\t: ";
        std::getline(std::cin, fac);
        if(!fac.empty())
        {
            bfac = s.setFaculty(fac);
            if (bfac)
                edited = true;
        }
        else
            break;
    } while (!bfac);

    // Ask for confirmation to edit
    if (edited)
    {
        std::cout << "\n\t----- NEW Student info -----\n";
        s.printDetails();
        do
        {
            std::cout << "\nConfirm changes? (Y/N): ";
            std::cin >> inputConfirm;
            std::cin.ignore();
            inputConfirm = tolower(inputConfirm);

            switch (inputConfirm)
            {
            case 'y':
                vec[studIndex] = s;
                std::cout << "Student succesfully edited!\n\n";
                return;

            case 'n':
                std::cout << "Student not edited\n\n";
                return;

            default:
                std::cout << "Invalid choice!\n\n";
                addLoop = true;
            }
        } while (addLoop);
    }
    else
        std::cout << "No changes made, returning...\n\n";
}

// Edit subject of student in the vector
void ReportCardSystem::editSub()
{
    Student *s;
    ReportEntry rOld, rNew;

    std::string sid, subid, subscore;
    
    bool bsubid, bsubscore;
    bool addLoop = true;
    bool intError, doubleError;
    
    int id, intSubID;
    int studIndex = -1;
    
    double doubleSubScore;

    char inputConfirm;

    // Ask for student id to search
    std::cout << "\n\t----- Edit Subject -----\n\n";
    do
    {
        std::cout << "Enter Student ID to edit (0 to cancel): ";
        std::getline(std::cin, sid);
        intError = false;
        try
        {
            id = stoi(sid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid ID! (10 digits)\n\n";
            intError = true;
        }

        if (!intError)
        {
            if (id == 0)
            {
                std::cout << "Cancelled editing subject\n\n";
                return;
            }
            studIndex = search(id);
            if(studIndex == -1)
                std::cout << "Student not found!\n\n";
        }
    } while(studIndex == -1);
    
    // s is a pointer because we need to directly edit the student in the vector
    s = &vec[studIndex];
    s->printInfo();

    // Ask for subject id to edit 
    do
    {
        std::cout << "\nWhich subject to edit?\t: ";
        std::getline(std::cin, subid);
        intError = false;
        try
        {
            intSubID = stoi(subid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid subject ID!\n\n";
            intError = true;
        }

        if (!intError)
            bsubid = s->getReportEntry(intSubID, rOld);
    } while (!bsubid);

    // Ask user to enter new score
    std::cout << "\n\t----- Editing Subject " << intSubID << " -----\n";
    rOld.printEntry();
    do
    {
        std::cout << "\nEnter new score: ";
        std::getline(std::cin, subscore);
        doubleError = false;
        try
        {
            doubleSubScore = std::stod(subscore);
        }
        catch (std::exception)
        {
            std::cout << "Invalid Subject Score!\n\n";
            doubleError = true;
        }

        if (!doubleError)
            bsubscore = rNew.setScore(doubleSubScore);
    } while (!bsubscore);

    std::cout << "\n\t--- Old entry ---";
    rOld.printEntry();
    std::cout << "\n\t--- New entry ---";
    rNew.setName(rOld.getName());
    rNew.printEntry();

    do
    {
        std::cout << "\n\nEdit this score? (Y/N): ";
        std::cin >> inputConfirm;
        std::cin.ignore();
        inputConfirm = tolower(inputConfirm);

        // Ask for confirmation
        switch (inputConfirm)
        {
        case 'y':
            s->editReportEntry(intSubID, rNew);
            std::cout << "Student successfully saved\n\n";
            addLoop = false;
            break;

        case 'n':
            addLoop = false;
            std::cout << "Score not edited\n\n";
            return;

        default:
            std::cout << "Invalid choice!";
            addLoop = true;
        }

    } while (addLoop);

    std::cout << "\n\t----- Saved student info -----\n";
    s->printInfo();
}

// Remove student from vector
void ReportCardSystem::removeStud()
{
     // Initialise variables
    Student *s;

    std::string sid;
    
    bool addLoop = true;
    bool intError;
    
    int id;
    int studIndex = -1;
    
    char inputConfirm;

    // Search student
    std::cout << "\n\t----- Delete Student -----\n\n";
    do
    {
        std::cout << "Enter Student ID to delete (0 to cancel): ";
        std::getline(std::cin, sid);
        intError = false;
        try
        {
            id = stoi(sid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid ID! (10 digits)\n\n";
            intError = true;
        }

        if (!intError)
        {
            if (id == 0)
            {
                std::cout << "\nCancelled editing student\n";
                return;
            }
            studIndex = search(id);
            if(studIndex == -1)
                std::cout << "Student not found!\n";
        }
    } while(studIndex == -1);

    s = &vec[studIndex];
    s->printInfo();

    // Ask confirmation to delete
    do
    {
        std::cout << "\nDelete student? (Y/N): ";
        std::cin >> inputConfirm;
        std::cin.ignore();
        inputConfirm = tolower(inputConfirm);

        switch (inputConfirm)
        {
        case 'y':
            vec.erase(vec.begin() + studIndex);
            std::cout << "Student succesfully deleted!\n\n";
            return;

        case 'n':
            std::cout << "Student not deleted\n\n";
            return;

        default:
            std::cout << "Invalid choice!\n";
            addLoop = true;
        }
    } while (addLoop);
}

// Remove subject from a student in the vector
void ReportCardSystem::removeSub()
{
    Student s;

    std::string sid, subid;
    
    bool bsid, bsubid;
    bool addLoop = true;
    bool intError;

    int id, intSubID;
    int studIndex = -1;
    
    char inputConfirm;

    // Ask for student id to search
    std::cout << "\n\t----- Remove Subject -----\n\n";
    do
    {
        std::cout << "Enter Student ID (0 to cancel): ";
        std::getline(std::cin, sid);
        intError = false;
        try
        {
            id = stoi(sid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid ID! (10 digits)\n\n";
            intError = true;
        }

        if (!intError)
        {
            if (id == 0)
            {
                std::cout << "Cancelled removing subject\n\n";
                return;
            }
            studIndex = search(id);
            if(studIndex == -1)
                std::cout << "Student not found!\n\n";
        }
    } while(studIndex == -1);

    s = vec[studIndex];
    s.printInfo();

    // Ask for subject id to edit 
    do
    {
        std::cout << "\nWhich subject to remove?: ";
        std::getline(std::cin, subid);
        intError = false;
        try
        {
            intSubID = stoi(subid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid subject ID!\n";
            intError = true;
        }
        if (!intError)
            bsubid = s.deleteReportEntry(intSubID);
    } while (!bsubid);

    std::cout << "\n\t----- NEW student info -----\n";
    s.printInfo();

    do
    {
        std::cout << "Save changes? (Y/N): ";
        std::cin >> inputConfirm;
        std::cin.ignore();
        inputConfirm = tolower(inputConfirm);
        
        switch (inputConfirm)
        {
        case 'y':
            vec[studIndex] = s;
            std::cout << "Changes successfully saved!\n\n";
            addLoop = false;
            break;

        case 'n':
            std::cout << "Changes not saved!\n\n";
            addLoop = false;
            break;
        
        default:
            std::cout << "Invalid choice!\n\n";
            addLoop = true;
        }
    } while (addLoop);
}

// Search for a given student in the vector
void ReportCardSystem::searchStud()
{
    std::string sid;
    bool intError;
    int id;
    int studIndex = -1;

    std::cout << "\n\t----- Search Student -----\n\n";
    do
    {
        std::cout << "Enter Student ID (0 to cancel): ";
        std::getline(std::cin, sid);
        intError = false;
        try
        {
            id = stoi(sid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid ID! (10 digits)\n\n";
            intError = true;
        }

        if (!intError)
        {
            if (id == 0)
            {
                std::cout << "Cancelled searching subject\n\n";
                return;
            }
            studIndex = search(id);
            if (studIndex == -1)
                std::cout << "Student not found!\n\n";
        }
    } while (studIndex == -1);
    vec[studIndex].printInfo();
}

// Prints multiple user specified students into a readable text file
void ReportCardSystem::printStudMul()
{
    std::ofstream file;
    Queue<Student> queue;
    std::string sid;
    bool intError = false;
    int id, bsidSearch;

    // Enter student information
    std::cout << "\n\t----- Add Student to Print List -----\n\n";
    do
    {
        std::cout << "Student ID (0 to finish / -1 to print all): ";
        std::getline(std::cin, sid);
        intError = false;
        try
        {
            id = stoi(sid);
        }
        catch (std::exception)
        {
            std::cout << "Invalid ID! (10 digits)\n\n";
            intError = true;
        }

        if (!intError)
        {
            if (id == 0)
                break;
            if (id == -1)
            {
                for (Student s : vec)
                {
                    queue.enqueue(s);
                }
                break;
            }
            bsidSearch = search(id);
            if (bsidSearch == -1)
                std::cout << "Student not found!\n\n";
            else
            {
                bool stackPushStatus = queue.enqueue(vec[bsidSearch]);
                if (stackPushStatus)
                    std::cout << "Student " << id << " added!\n";
                else
                    std::cout << "Failed to add student " << id << "\n";
            }
        }

    // If student id not 0 or, 
    // if student not found, repeat
    } while (id != 0 || bsidSearch == -1);

    if (!queue.is_empty())
    {
        std::string tempFilename;
        if (queue.get_size() == 1)
        {
            Student s;
            queue.get_front(s);
            tempFilename = "Student-" + std::to_string(s.getID()) + ".txt";
        }
        else
        {
            Student s_front;
            Student s_back;
            queue.get_front(s_front);
            queue.get_back(s_back);
            tempFilename = "StudentList-"
                            + std::to_string(queue.get_size())
                            + "-" + std::to_string(s_front.getID())
                            + "-" + std::to_string(s_back.getID())
                            + ".txt";
        }
        try
        {
            int numOfStud = 0;
            Student tempStud;
            file.open(tempFilename);
            while (queue.dequeue(tempStud))
            {
                file << tempStud.getDetails() << "\n=========================\n\n";
                numOfStud++;
            }
            std::cout << "\nSuccessfully exported " << numOfStud << " students to " << tempFilename << "\n\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
    {
        std::cout << "No student exported.\n";
    }
}

// Wrapper function for search
int ReportCardSystem::search(int query)
{
    return Util::binarysearch(vec, 0, vec.size() - 1, query);
}

// Wrapper function to sort the vector
void ReportCardSystem::sort()
{
    Util::quicksort(vec, 0, vec.size() - 1);
}

// Write to file the contents of vector
void ReportCardSystem::write_file(std::string filename)
{
    Student s;
    int vecSize = vec.size();

    try
    {
        outFile.open(filename, std::ios::binary);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if (!outFile.is_open())
    {
        std::cout << "\nNo data file available!\n";
        return;
    }

    std::cout << "\n\t\tWriting data to " << filename << "\n";
    if (filename == _STUDENT_FILE)
    {
        outFile.write((char*)&vecSize, sizeof(vecSize));
        for (int i = 0; i < vecSize; i++)
        {
            s = vec[i];
            outFile.write((char*)&s, sizeof(s));
        }
    }
    outFile.close();
    std::cout << "\t\tSuccessfully saved data to " << filename << "\n";
}

// Read to vector the contents of file
void ReportCardSystem::read_file(std::string filename)
{
    Student s;
    int vecSize;

    try
    {
        inFile.open(filename, std::ios::binary);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if (!inFile.is_open())
    {
        std::cout << "\nNo data file available!\n";
        return;
    }

    std::cout << "\n\t\tReading " << filename << "\n";
    if (filename == _STUDENT_FILE)
    {
        inFile.read((char*)&vecSize, sizeof(vecSize));
        for (int i = 0; i < vecSize; i++)
        {
            inFile.read((char*)&s, sizeof(s));
            vec.push_back(s);
        }
    }
    inFile.close();
}

// Main menu prompt
char ReportCardSystem::menu_prompt(char first, char last)
{
    char choice;
    do
    {
        std::cout << "\n\t\tEnter choice (" << first << "-" << last << "): ";
        std::cin >> choice;
        std::cin.ignore();
        if (isdigit(choice) && choice >= first && choice <= last)
            return choice;
        else if (choice == 'p')
            return choice;
        else
            return -1;
    } while (true);
}

// Handles exit procedure
bool ReportCardSystem::exit_internal()
{
    std::string confirm;
    bool exitStatus = false, cont = true;
    Util::clear();
    do
    {
        std::cout << "\n\t\tAre you sure you want to exit? (Y/N): ";
        std::getline(std::cin, confirm);

        if (confirm == "y" || confirm == "Y" )
        {
            exitStatus = true;
            cont = false;
        }
        else if (confirm == "n" || confirm == "N" )
        {
            exitStatus = false;
            cont = false;
        }
    } while (cont);
    if (exitStatus)
    {
        Util::clear();
        std::cout << "\n========================================================================================="
            << "\n|\t   _____    ____     ____    _____    ____   __     __  ______     _ \t\t|"
            << "\n|\t  / ____|  / __ \\   / __ \\  |  __ \\  |  _ \\  \\ \\   / / |  ____|   | |\t\t|"
            << "\n|\t | |  __  | |  | | | |  | | | |  | | | |_) |  \\ \\_/ /  | |__      | |\t\t|"
            << "\n|\t | | |_ | | |  | | | |  | | | |  | | |  _ <    \\   /   |  __|     | |\t\t|"
            << "\n|\t | |__| | | |__| | | |__| | | |__| | | |_) |    | |    | |____    |_|\t\t|"
            << "\n|\t  \\_____|  \\____/   \\____/  |_____/  |____/     |_|    |______|   (_)\t\t|"
            << "\n=========================================================================================\n\n"
            << std::endl;
        std::chrono::seconds timespan(3);
        std::this_thread::sleep_for(timespan);
        Util::clear();
    }
    return exitStatus;
}

// [Debug] Prints vector content (student id)
void ReportCardSystem::printVec()
{
    if (vec.size() > 0)
        for (Student s : vec)
            s.printDetails();
    else
        std::cout << "No students!\n";
    std::endl(std::cout);
}

// Constructor
ReportCardSystem::ReportCardSystem()
{
    read_file(_STUDENT_FILE);
    sort();
    mainMenu();
}

// Destructor
ReportCardSystem::~ReportCardSystem()
{
    write_file(_STUDENT_FILE);
    Util::clear();
}
