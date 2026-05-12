#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//******************************************************************************
//                           GREGORIAN CALENDAR FUNCTIONS
//******************************************************************************

/*
 * Function: getDaysInMonthGreg
 * Purpose: Returns the number of days in a given month for Gregorian calendar
 * Parameters: month - The month number (1-12)
 *            year - The year to check for leap years
 * Returns: Number of days in the specified month
 */
int getDaysInMonthGreg(int month, int year) {
    // February has special handling for leap years
    if(month == 2) {
        // Leap year calculation: divisible by 4, but not by 100, unless also by 400
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
    }
    // April, June, September, November have 30 days
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    // All other months have 31 days
    else
        return 31;
}

/*
 * Function: getStartDayGreg
 * Purpose: Uses Zeller's Congruence to find the day of week for 1st of month
 * Parameters: year - The year
 *            month - The month (1-12)
 * Returns: Day of week (0=Sunday, 1=Monday, ..., 6=Saturday)
 * Note: Zeller's formula treats January and February as months 13 and 14 of previous year
 */
int getStartDayGreg(int year, int month) {
    // Zeller's formula treats Jan and Feb as months 13 and 14 of previous year
    if(month <= 2) {
        month += 12;    // Convert Jan/Feb to months 13/14
        year--;         // Use previous year for calculation
    }
    
    // Zeller's Congruence formula variables
    int q = 1;          // Day of month (always 1st for our purpose)
    int m = month;      // Month (adjusted above if needed)
    int k = year % 100; // Year of the century
    int j = year / 100; // Zero-based century

    // Apply Zeller's formula
    int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return (h + 6) % 7; // Convert to standard format: 0=Sunday, 1=Monday, ...
}

/*
 * Function: printMonthHeaderGreg
 * Purpose: Prints a formatted header for a Gregorian calendar month
 * Parameters: month - Month number (1-12)
 *            year - Year to display
 */
void printMonthHeaderGreg(int month, int year) {
    // Array of month names (index 0 unused for easier 1-12 indexing)
    string months[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    
    // Print month and year with centered formatting
    cout << "\n      "<< months[month] << " " << year << endl;
    // Print day abbreviations header
    cout << "  Su  Mo  Tu  We  Th  Fr  Sa" << endl;
}

/*
 * Function: printMonthGreg
 * Purpose: Prints a complete monthly calendar for Gregorian calendar
 * Parameters: month - Month number (1-12)
 *            year - Year to display
 */
void printMonthGreg(int month, int year) {
    int days = getDaysInMonthGreg(month, year);     // Total days in this month
    int startDay = getStartDayGreg(year, month);    // Day of week for 1st day

    printMonthHeaderGreg(month, year);

    // Print leading spaces for days before the 1st
    for(int i = 0; i < startDay; i++)
        cout << "    ";

    // Print each day of the month
    for(int day = 1; day <= days; day++) {
        cout << setw(4) << day;
        // Start new line after Saturday (when position divisible by 7)
        if((day + startDay) % 7 == 0)
            cout << endl;
    }
    cout << endl;
}

/*
 * Function: printYearCalendarGreg
 * Purpose: Prints the complete yearly calendar for Gregorian calendar
 * Parameters: year - Year to display (all 12 months)
 */
void printYearCalendarGreg(int year) {
    cout << "\n" << string(60, '*') << endl;
    cout << "                    GREGORIAN CALENDAR " << year << endl;
    cout << string(60, '*') << endl;
    
    for(int month = 1; month <= 12; month++) {
        printMonthGreg(month, year);
    }
}

//******************************************************************************
//                           ETHIOPIAN CALENDAR FUNCTIONS
//******************************************************************************

/*
 * Function: isLeapYear
 * Purpose: Determines if an Ethiopian year is a leap year
 * Parameters: year - Ethiopian year to check
 * Returns: true if leap year, false otherwise
 * Note: Ethiopian leap year rule: (year + 1) divisible by 4
 */
bool isLeapYear(int year) {
    return (year + 1) % 4 == 0;
}

/*
 * Function: getFirstDayOfYearEt
 * Purpose: Calculates the first day of an Ethiopian year
 * Parameters: year - Ethiopian year
 * Returns: Day of week (0 = Monday, ..., 6 = Sunday)
 */
int getFirstDayOfYearEt(int year) {
    return ((year + 5500) + ((year + 5500) / 4)) % 7;
}
// Array of Ethiopian month names (13 months total)
const string ETHIOPIAN_MONTHS[13] = {
    "Meskerem", "Tikimt", "Hidar", "Tahsas", "Tir", "Yekatit",
    "Megabit", "Miyazia", "Ginbot", "Sene", "Hamle", "Nehase", "Pagume"
};

/*
 * Function: getDaysInMonthEt
 * Purpose: Returns number of days in an Ethiopian month
 * Parameters: month - Month number (1-13)
 *            year - Year (needed for Pagume leap year calculation)
 * Returns: Number of days in the month
 * Note: Months 1-12 have 30 days, Pagume (13) has 5 or 6 days
 */
int getDaysInMonthEt(int month, int year) {
    // First 12 months always have 30 days
    if(month >= 1 && month <= 12)
        return 30;
    // Pagume (13th month): 6 days in leap year, 5 in regular year
    else if(month == 13)
        return isLeapYear(year) ? 6 : 5;
    else
        return -1; // Invalid month number
}

/*
 * Function: getFirstDayOfMonthEt
 * Purpose: Calculates the first day of week for a specific Ethiopian month
 * Parameters: year - Ethiopian year
 *            monthIndex - Month number (1-13)
 * Returns: Day of week (0 = Monday, ..., 6 = Sunday)
 */
int getFirstDayOfMonthEt(int year, int monthIndex) {
    int startDay = getFirstDayOfYearEt(year);   // Start with first day of year
    
    // Add days from all previous months to find this month's start day
    for(int i = 1; i < monthIndex; ++i) {
        startDay = (startDay + getDaysInMonthEt(i, year)) % 7;
    }
    return startDay;
}

/*
 * Function: printMonthHeaderEt
 * Purpose: Prints header for Ethiopian calendar month
 * Parameters: monthIndex - Month number (1-13)
 */
void printMonthHeaderEt(int monthIndex) {
    cout << "\n  " << ETHIOPIAN_MONTHS[monthIndex - 1] << endl;
    cout << "Mo Tu We Th Fr Sa Su" << endl;    // Ethiopian week starts with Monday
}

/*
 * Function: printMonthBodyEt
 * Purpose: Prints the days of an Ethiopian calendar month
 * Parameters: year - Ethiopian year
 *            monthIndex - Month number (1-13)
 *            startDay - Day of week for first day of month
 */
void printMonthBodyEt(int year, int monthIndex, int startDay) {
    int days = getDaysInMonthEt(monthIndex, year);  // Total days in this month

    // Print leading spaces for days before the 1st
    for(int i = 0; i < startDay; ++i)
        cout << "   ";

    // Print each day of the month
    for(int day = 1; day <= days; ++day) {
        cout << setw(2) << day << " ";
        startDay = (startDay + 1) % 7;  // Move to next day of week
        
        // Start new line after Sunday (day 0 of next week)
        if (startDay == 0)
            cout << endl;
    }

    // End with newline if month doesn't end on Sunday
    if(startDay != 0)
        cout << endl;
}

/*
 * Function: printMonthEt
 * Purpose: Prints complete Ethiopian calendar month (header + body)
 * Parameters: year - Ethiopian year
 *            monthIndex - Month number (1-13)
 */
void printMonthEt(int year, int monthIndex) {
    int startDay = getFirstDayOfMonthEt(year, monthIndex);
    printMonthHeaderEt(monthIndex);
    printMonthBodyEt(year, monthIndex, startDay);
}

/*
 * Function: printEthiopianCalendar
 * Purpose: Prints the complete Ethiopian yearly calendar (all 13 months)
 * Parameters: year - Ethiopian year to display
 */
void printEthiopianCalendar(int year) {
    cout << "\n" << string(60, '*') << endl;
    cout << "                    ETHIOPIAN CALENDAR " << year << endl;
    cout << string(60, '*') << endl;
    
    int startDay = getFirstDayOfYearEt(year);
    for(int month = 1; month <= 13; ++month) {
        printMonthEt(year, month);
    }
}

/*
 * Function: getDayOfWeekEt
 * Purpose: Determines day of week for any Ethiopian date
 * Parameters: year - Ethiopian year
 *            month - Ethiopian month (1-13)
 *            day - Day of month
 * Returns: Day of week as string
 * Note: Uses Tinteyon calculation method
 */

string getDayOfWeekEt(int year, int month, int day){
    int startDay = getFirstDayOfYearEt(year);   // Get first day of the year
    
    // Array of weekday names (Saturday to Friday order for calculation)
    const string weeks[7] = {
        "Saturday","Sunday","Monday","Tuesday", "Wednesday","Thursday", "Friday"
    };
    
    // Tinteyon mapping for Ethiopian calendar calculation
    const int tinteKemer[7] = {6,7,1,2,3,4,5};
    int tinteyon = tinteKemer[startDay];
    
    // Ethiopian formula: tinteyon + day + (2 * month)
    int dayOfweek = (tinteyon + (2 * month) + day) % 7;
    return weeks[dayOfweek];
}

//******************************************************************************
//                              BAHIRE HASAB FUNCTIONS
//******************************************************************************

/*
 * Function: getMetqi
 * Purpose: Calculates Metqi value for Bahire Hasab computation
 * Parameters: year - Ethiopian year
 * Returns: Metqi value (used in Easter calculation)
 * Note: Based on 19-year cycle calculation
 */

int getMetqi(int year){
    int wenber = ((5500 + year) % 19) - 1;     // Calculate Wenber (position in 19-year cycle)
    return (wenber * 19) % 30;                 // Calculate Metqi value
}

/*
 * Function: getBahireHasabComponents
 * Purpose: Determines the day component for Bahire Hasab calculation
 * Parameters: year - Ethiopian year
 * Returns: Day of week as string for the calculated date
 */
string getBahireHasabComponents(int year){
    string bealeMetqi;      // Variable to store the calculated day
    int metqi = getMetqi(year);
    
    // Determine month and day based on Metqi value
    if(metqi < 14){
        bealeMetqi = getDayOfWeekEt(year, 2, metqi);        // Tikimt month
    } else if(metqi > 14){
        bealeMetqi = getDayOfWeekEt(year, 1, metqi);        // Meskerem month
    } else if(metqi == 0){
        bealeMetqi = getDayOfWeekEt(year, 1, 30);           // Last day of Meskerem
    }

    return bealeMetqi;
}

/*
 * Function: getTewsak
 * Purpose: Calculates Tewsak value for Bahire Hasab
 * Parameters: year - Ethiopian year
 * Returns: Tewsak value (8 minus day index)
 */


int getTewsak(int year){
    // Array of weekday names for matching
    const string daysofWeek[7] = {
        "Saturday", "Sunday", "Monday",
        "Tuesday", "Wednesday", "Thursday", "Friday"
    };

    string days = getBahireHasabComponents(year);   // Get the day from Bahire Hasab

    // Find the day index and calculate Tewsak (decreases from 8 to 2)
    for (int i = 0; i < 7; ++i) {
        if (daysofWeek[i] == days) {
            return 8 - i;
        }
    }

    return -1;  // Invalid day (should not occur)
}

/*
 * Function: getNinevehMonth
 * Purpose: Determines which month Nineveh (start of fasting period) falls in
 * Parameters: year - Ethiopian year
 * Returns: Month name as string ("Tir" or "Yekatit")
 */
string getNinevehMonth(int year){
    string ninevehMonth;
    int tewsak = getTewsak(year);   // Get Tewsak value
    int metqi = getMetqi(year);     // Get Metqi value
    
    // Logic to determine the month based on Metqi and Tewsak values
    if (metqi == 0) {
        ninevehMonth = "Yekatit";
    }
    else if (metqi < 14) {
        ninevehMonth = "Yekatit";
    }
    else if (metqi > 14 && (metqi + tewsak) > 30) {
        ninevehMonth = "Yekatit";
    }
    else if (metqi > 14) {
        ninevehMonth = "Tir";
    }

    return ninevehMonth;
}

/*
 * Function: getMonthIndex
 * Purpose: Finds the index of a month in the ETHIOPIAN_MONTHS array
 * Parameters: month - Month name as string
 * Returns: Index (0-12) or -1 if not found
 */
int getMonthIndex(const std::string& month) {
    // Search through Ethiopian months array to find matching month
    for (int i = 0; i < 13; ++i)
        if (ETHIOPIAN_MONTHS[i] == month) return i;
    return -1;  // Month not found
}

/*
 * Function: addDays
 * Purpose: Adds specified number of days to an Ethiopian date and prints result
 * Parameters: month - Starting month name
 *            day - Starting day
 *            add - Number of days to add
 *            year - Ethiopian year
 */
void addDays(string month, int day, int add, int year) {
    int i = getMonthIndex(month);   // Get month index
    if (i == -1) {
        cout << "Invalid month name provided!\n";
        return;
    }

    // Add days, handling month transitions
    while (add > 0) {
        int daysLeft = getDaysInMonthEt(i + 1, year) - day;  // Days remaining in current month
        
        if (add <= daysLeft) {
            day += add;     // Remaining days fit in current month
            break;
        } else {
            add -= (daysLeft + 1);  // Move to next month
            i = (i + 1) % 13;       // Cycle through months (0-12)
            day = 1;                // Start from first day of new month
        }
    }

    // Display the calculated date
    cout << ETHIOPIAN_MONTHS[i] << " " << day << "\n";
}

/*
 * Function: getMebajaHamer
 * Purpose: Calculates Mebaja Hamer value for Bahire Hasab
 * Parameters: year - Ethiopian year
 * Returns: Calculated Mebaja Hamer value
 */
int getMebajaHamer(int year){
    int tewsak = getTewsak(year);   // Get Tewsak value
    int metqi = getMetqi(year);     // Get Metqi value
    return (tewsak + metqi) % 30;   // Calculate Mebaja Hamer
}

/*
 * Function: printBahreHasab
 * Purpose: Prints complete Bahire Hasab calculations for Ethiopian religious calendar
 * Parameters: year - Ethiopian year
 * Note: Displays all major religious holidays and fasting periods
 */
void printBahreHasab(int year){
    int mebajaHamer = getMebajaHamer(year);     // Calculate Mebaja Hamer
    string ninevehMonth = getNinevehMonth(year); // Determine Nineveh month
    
    cout << "\n" << string(60, '=') << endl;
    cout << "                     BAHIRE HASAB " << year << endl;
    cout << "                       (በአላት)" << endl;
    cout << string(60, '=') << endl;
    
    cout << "ነነዌ (Nineveh):           " << ninevehMonth << " " << mebajaHamer << endl;
    cout << "ዓቢይ ጾም (Great Fast):      ";
    addDays(ninevehMonth, mebajaHamer, 14, year);
    
    cout << "ደብረ ዘይት (Debre Zeit):     ";
    addDays(ninevehMonth, mebajaHamer, 41, year);
    
    cout << "ሆሳዕና (Hosanna):           ";
    addDays(ninevehMonth, mebajaHamer, 62, year);
    
    cout << "ስቅለት (Crucifixion):       ";
    addDays(ninevehMonth, mebajaHamer, 67, year);
    
    cout << "ትንሳዔ (Easter):            ";
    addDays(ninevehMonth, mebajaHamer, 69, year);
    
    cout << "ርክበ ክህነት (Rikbe Kehnet):  ";
    addDays(ninevehMonth, mebajaHamer, 93, year);
    
    cout << "ዕርገት (Ascension):         ";
    addDays(ninevehMonth, mebajaHamer, 108, year);
    
    cout << "ጰራቅሊጦስ (Pentecost):      ";
    addDays(ninevehMonth, mebajaHamer, 118, year);
    
    cout << "ፆመ ሐዋርያት (Apostles Fast): ";
    addDays(ninevehMonth, mebajaHamer, 119, year);
    
    cout << "ፆመ ድህነት (Salvation Fast): ";
    addDays(ninevehMonth, mebajaHamer, 121, year);
    
    cout << string(60, '=') << endl;
}

//******************************************************************************
//                           CALENDAR CONVERTER FUNCTIONS
//******************************************************************************

/*
 * Function: isGregorianLeap
 * Purpose: Checks if a Gregorian year is a leap year
 * Parameters: year - Gregorian year to check
 * Returns: true if leap year, false otherwise
 */

bool isGregorianLeap(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

/*
 * Function: EthiopianToGregorian
 * Purpose: Converts Ethiopian date to Gregorian date
 * Parameters: ethYear - Ethiopian year
 *            ethMonth - Ethiopian month (1-13)
 *            ethDay - Ethiopian day
 * Note: Ethiopian New Year typically falls on September 11 or 12 in Gregorian calendar
 */
void EthiopianToGregorian(int ethYear, int ethMonth, int ethDay) {
    int gYear = ethYear + 7;    // Approximate Gregorian year (Ethiopian + 7/8 years)

    // Determine if Ethiopian new year falls on Sep 11 or 12 in target Gregorian year
    int gNewYearDay = isLeapYear(gYear + 1) ? 12 : 11;
    int gMonth = 9;     // September
    int gDay = gNewYearDay;

    // Calculate total days since Meskerem 1 (Ethiopian New Year)
    int daysToAdd = (ethMonth - 1) * 30 + (ethDay - 1);

    // Add the calculated days to the Gregorian new year date
    while (daysToAdd > 0) {
        int daysInMonth = getDaysInMonthGreg(gMonth, gYear);
        int daysLeftInMonth = daysInMonth - gDay;

        if (daysToAdd <= daysLeftInMonth) {
            gDay += daysToAdd;  // Remaining days fit in current month
            break;
        } else {
            daysToAdd -= (daysLeftInMonth + 1);  // Move to next month
            gDay = 1;
            gMonth++;
            if (gMonth > 12) {  // Handle year transition
                gMonth = 1;
                gYear++;
            }
        }
    }

    cout << "Gregorian Date: " << gDay << "/" << gMonth << "/" << gYear << endl;
}

/*
 * Function: GregorianToEthiopian
 * Purpose: Converts Gregorian date to Ethiopian date
 * Parameters: gYear - Gregorian year
 *            gMonth - Gregorian month (1-12)
 *            gDay - Gregorian day
 * Note: Handles the offset between calendar systems and leap year differences
 */
void GregorianToEthiopian(int gYear, int gMonth, int gDay) {
    // Determine Ethiopian New Year date in Gregorian calendar for this year
    int ethNewYearDay = isGregorianLeap(gYear) ? 12 : 11; // September 11 or 12

    // Check if current date is before or after Ethiopian New Year
    bool isAfterEthNewYear = (gMonth > 9) || (gMonth == 9 && gDay >= ethNewYearDay);

    // Calculate corresponding Ethiopian year
    int ethYear = isAfterEthNewYear ? gYear - 7 : gYear - 8;

    // Calculate days elapsed since Ethiopian New Year
    int daysSinceNewYear = 0;

    if (isAfterEthNewYear) {
        // Count days from current Ethiopian New Year (September)
        daysSinceNewYear += gDay - ethNewYearDay;
        for (int m = 10; m < gMonth; m++) {
            daysSinceNewYear += getDaysInMonthGreg(m, gYear);
        }
    } else {
        // Count days from previous Ethiopian New Year
        daysSinceNewYear += getDaysInMonthGreg(9, gYear-1) - ethNewYearDay;
        
        // Add days from October-December of previous year
        for (int m = 10; m <= 12; m++) {
            daysSinceNewYear += getDaysInMonthGreg(m, gYear-1);
        }
        
        // Add days from January to current month of current year
        for (int m = 1; m < gMonth; m++) {
            daysSinceNewYear += getDaysInMonthGreg(m, gYear);
        }
        
        daysSinceNewYear += gDay;  // Add current day
    }

    // Convert to Ethiopian date (months 1-12 have 30 days, month 13 has 5-6 days)
    int ethMonth = daysSinceNewYear / 30 + 1;
    int ethDay = daysSinceNewYear % 30 + 1;

    // Handle Pagume (13th month) and year transitions
    if (ethMonth > 13) {
        ethMonth = 1;
        ethYear++;
    } else if (ethMonth == 13) {
        int daysInPagume = isGregorianLeap(gYear + 1) ? 6 : 5;
        if (ethDay > daysInPagume) {
            ethDay -= daysInPagume;
            ethMonth = 1;
            ethYear++;
        }
    }

    cout << "Ethiopian Date: " << ethYear << "/" << ethMonth << "/" << ethDay << endl;
}

//******************************************************************************
//                                  MAIN FUNCTION
//******************************************************************************



/*
 * Function: displayAssignmentInfo
 * Purpose: Displays group assignment information
 */
void displayAssignmentInfo() {
    cout << "\n" << string(60, '=') << endl;
    cout << "                = Group Members =" << endl;
    cout << " 1. Adonay Teferi --- UGR/0142/17" << endl;
    cout << " 2. Natunael Esatu --- UGR/7514/17" << endl;
    cout << " 3. Tedros Meresa --- UGR/2084/17" << endl;
    cout << " 4. Yeabtsega Belete --- UGR/9879/17" << endl;
    cout << " 5. Yishak Tamirat --- UGR/8090/17" << endl;
    cout << " 6. Ytbarek Tesfaye --- UGR/4389/17" << endl;
    cout << " 7. Yosen Grima --- UGR/1758/17" << endl;
    cout << "\n                = Submitted to =" << endl;
    cout << "              Birhaneselasie Abebe" << endl;
    cout << "\n               == Submission Date ==" << endl;
    cout << "                 June 2, 2025" << endl;
    cout << string(60, '=') << endl;
}

int main() {
    int choice;     // Variable to store user's menu choice

    // Display assignment header (shown only once)
    cout << "\n" << string(60, '=') << endl;
    cout << "                Addis Ababa University" << endl;
    cout << "             Department of Information Systems" << endl;
    cout << "            Computer Programming group Assignment" << endl;
    cout << string(60, '=') << endl;

    // Display welcome message
    cout << "\n" << string(70, '*') << endl;
    cout << "                    WELCOME TO CALENDAR SYSTEM" << endl;
    cout << "              Gregorian, Ethiopian & Bahire Hasab" << endl;
    cout << string(70, '*') << endl;

    while (true) {        // Display main menu with attractive formatting
        cout << "\n" << string(50, '=') << endl;
        cout << "             CALENDAR MAIN MENU" << endl;
        cout << string(50, '=') << endl;
        cout << "  [1] Gregorian Calendar" << endl;
        cout << "  [2] Ethiopian Calendar" << endl;
        cout << "  [3] Calendar Converter" << endl;
        cout << "  [4] Bahire Hasab (Ethiopian Religious Calendar)" << endl;
        cout << "  [5] Exit Program" << endl;
        cout << "  [6] About this assignment" << endl;
        cout << string(50, '=') << endl;
        cout << "Please enter your choice (1-6): ";
        cin >> choice;

        // Input validation
        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n*** ERROR: Invalid input! Please enter a number between 1 and 6. ***\n";
            continue;
        }

        // Exit option with farewell message
        if (choice == 5) {
            cout << "\n" << string(50, '*') << endl;
            cout << "         Thank you for using Calendar System!" << endl;
            cout << "                Have a wonderful day!" << endl;
            cout << string(50, '*') << endl;
            break;
        }

        // ABOUT ASSIGNMENT SECTION
        if (choice == 6) {
            displayAssignmentInfo();
            continue;
        }

        // GREGORIAN CALENDAR SECTION
        if (choice == 1) {
            int gChoice;    // Variable for Gregorian submenu choice
            cout << "\n" << string(40, '-') << endl;
            cout << "         GREGORIAN CALENDAR OPTIONS" << endl;
            cout << string(40, '-') << endl;
            cout << "  [1] Display Full Year Calendar" << endl;
            cout << "  [2] Display Single Month Calendar" << endl;
            cout << "  [3] Find Day of Week for Date" << endl;
            cout << string(40, '-') << endl;
            cout << "Choose option (1-3): ";
            cin >> gChoice;

            // Input validation for Gregorian submenu
            if (cin.fail() || gChoice < 1 || gChoice > 3) {
                cin.clear(); 
                cin.ignore(10000, '\n');
                cout << "\n*** ERROR: Invalid input. Please try again. ***\n"; 
                continue;
            }

            int year, month, day;   // Variables for date input
            switch (gChoice) {
                case 1:
                    cout << "\nEnter year: ";
                    cin >> year;
                    if (cin.fail()) {
                        cin.clear(); 
                        cin.ignore(10000, '\n');
                        cout << "*** ERROR: Invalid year format. ***\n"; 
                        break;
                    }
                    printYearCalendarGreg(year);
                    break;
                    
                case 2:
                    cout << "\nEnter month (1-12): "; 
                    cin >> month;
                    cout << "Enter year: "; 
                    cin >> year;
                    if (month < 1 || month > 12 || cin.fail()) {
                        cout << "*** ERROR: Invalid month. Please enter 1-12. ***\n"; 
                        cin.clear(); 
                        cin.ignore(10000, '\n');
                        break;
                    }
                    printMonthGreg(month, year);
                    break;
                    
                case 3:
                    cout << "\nEnter date (DD MM YYYY): ";
                    cin >> day >> month >> year;
                    if (month < 1 || month > 12 || day < 1 || day > getDaysInMonthGreg(month, year) || cin.fail()) {
                        cout << "*** ERROR: Invalid date format or date doesn't exist. ***\n"; 
                        cin.clear(); 
                        cin.ignore(10000, '\n');
                        break;
                    }
                    {
                        // Array of weekday names
                        string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
                        int startDay = getStartDayGreg(year, month);    // Get first day of month
                        int weekday = (startDay + day - 1) % 7;         // Calculate day of week
                        cout << "\n==> Day of the week: " << days[weekday] << " <==" << endl;
                    }
                    break;
            }
        }        

        // ETHIOPIAN CALENDAR SECTION
        else if (choice == 2) {
            int eChoice;    // Variable for Ethiopian submenu choice
            cout << "\n" << string(40, '-') << endl;
            cout << "         ETHIOPIAN CALENDAR OPTIONS" << endl;
            cout << string(40, '-') << endl;
            cout << "  [1] Display Full Year Calendar" << endl;
            cout << "  [2] Display Single Month Calendar" << endl;
            cout << "  [3] Find Day of Week for Date" << endl;
            cout << string(40, '-') << endl;
            cout << "Choose option (1-3): ";
            cin >> eChoice;

            // Input validation for Ethiopian submenu
            if (cin.fail() || eChoice < 1 || eChoice > 3) {
                cin.clear(); 
                cin.ignore(10000, '\n');
                cout << "\n*** ERROR: Invalid input. Please try again. ***\n"; 
                continue;
            }

            int year, month, day;   // Variables for Ethiopian date input
            switch (eChoice) {
                case 1:
                    cout << "\nEnter Ethiopian year: ";
                    cin >> year;
                    if (cin.fail()) {
                        cin.clear(); 
                        cin.ignore(10000, '\n');
                        cout << "*** ERROR: Invalid year format. ***\n"; 
                        break;
                    }
                    printEthiopianCalendar(year);
                    break;
                    
                case 2:
                    cout << "\nEnter Ethiopian month (1-13): "; 
                    cin >> month;
                    cout << "Enter year: "; 
                    cin >> year;
                    if (month < 1 || month > 13 || cin.fail()) {
                        cout << "*** ERROR: Invalid month. Ethiopian calendar has 13 months (1-13). ***\n"; 
                        cin.clear(); 
                        cin.ignore(10000, '\n');
                        break;
                    }
                    printMonthEt(year, month);
                    break;
                    
                case 3:
                    cout << "\nEnter Ethiopian date (DD MM YYYY): ";
                    cin >> day >> month >> year;
                    if (month < 1 || month > 13 || day < 1 || day > getDaysInMonthEt(month, year) || cin.fail()) {
                        cout << "*** ERROR: Invalid Ethiopian date format or date doesn't exist. ***\n"; 
                        cin.clear(); 
                        cin.ignore(10000, '\n');
                        break;
                    }
                    cout << "\n==> Day of the week: " << getDayOfWeekEt(year, month, day) << " <==" << endl;
                    break;
            }
        }

        // CALENDAR CONVERTER SECTION
        else if (choice == 3) {
            int convChoice;     // Variable for converter submenu choice
            cout << "\n" << string(40, '-') << endl;
            cout << "           CALENDAR CONVERTER" << endl;
            cout << string(40, '-') << endl;
            cout << "  [1] Gregorian -> Ethiopian" << endl;
            cout << "  [2] Ethiopian -> Gregorian" << endl;
            cout << string(40, '-') << endl;
            cout << "Choose conversion (1-2): ";
            cin >> convChoice;

            // Input validation for converter submenu
            if (cin.fail() || (convChoice != 1 && convChoice != 2)) {
                cin.clear(); 
                cin.ignore(10000, '\n');
                cout << "\n*** ERROR: Invalid input. Please choose 1 or 2. ***\n"; 
                continue;
            }

            int day, month, year;   // Variables for date conversion
            if (convChoice == 1) {
                cout << "\nEnter Gregorian date (DD MM YYYY): ";
                cin >> day >> month >> year;
                if (month < 1 || month > 12 || day < 1 || day > getDaysInMonthGreg(month, year) || cin.fail()) {
                    cout << "*** ERROR: Invalid Gregorian date format or date doesn't exist. ***\n"; 
                    cin.clear(); 
                    cin.ignore(10000, '\n');
                    continue;
                }
                cout << "\n--- CONVERSION RESULT ---" << endl;
                GregorianToEthiopian(year, month, day);
            } else {
                cout << "\nEnter Ethiopian date (DD MM YYYY): ";
                cin >> day >> month >> year;
                if (month < 1 || month > 13 || day < 1 || day > getDaysInMonthEt(month, year) || cin.fail()) {
                    cout << "*** ERROR: Invalid Ethiopian date format or date doesn't exist. ***\n"; 
                    cin.clear(); 
                    cin.ignore(10000, '\n');
                    continue;
                }
                cout << "\n--- CONVERSION RESULT ---" << endl;
                EthiopianToGregorian(year, month, day);
            }
        }

        // BAHIRE HASAB SECTION
        else if (choice == 4) {
            int year;   // Variable for Ethiopian year input
            cout << "\n" << string(40, '-') << endl;
            cout << "            BAHIRE HASAB" << endl;
            cout << "     (Ethiopian Religious Calendar)" << endl;
            cout << string(40, '-') << endl;
            cout << "Enter Ethiopian year for Bahire Hasab calculation: ";
            cin >> year;
            
            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(10000, '\n');
                cout << "*** ERROR: Invalid year format. ***\n"; 
                continue;
            }
            
            printBahreHasab(year);
        }
    }

    return 0;
}
