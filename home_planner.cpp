#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

// ═════
//  STRUCTURES
// ══════

struct Room {
    string name;
    float  length;
    float  width;
    float  area;
    string type;   // bedroom / kitchen / bathroom / hall / other
};

struct HomePlan {
    string ownerName;
    string plotLocation;
    float  plotLength;
    float  plotWidth;
    float  plotArea;
    float  usableArea;
    vector<Room> rooms;
    float  totalUsed;
    float  remaining;
};

// ══════
//  CONSTANTS
// ═════════

const float WALL_DEDUCTION   = 0.10f;
const float MIN_ROOM_SIZE    = 20.0f;
const float COST_PER_SQFT_LO = 1200.0f;   // Rs. budget
const float COST_PER_SQFT_HI = 2000.0f;   // Rs. premium

// ═════════
//  UTILITY HELPERS
// ════════

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void printLine(char c = '-', int n = 65) {
    cout << string(n, c) << "\n";
}

void printTitle(const string& title) {
    printLine('=');
    int pad = (65 - title.size()) / 2;
    cout << string(pad, ' ') << title << "\n";
    printLine('=');
}

void printSection(const string& title) {
    cout << "\n";
    printLine('-');
    cout << "  >> " << title << "\n";
    printLine('-');
}

float getPositiveFloat(const string& prompt, float minVal = 0.1f) {
    float val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= minVal) return val;
        cout << "  [!] Invalid input. Enter a number >= " << minVal << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getIntInRange(const string& prompt, int lo, int hi) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= lo && val <= hi) return val;
        cout << "  [!] Enter a number between " << lo << " and " << hi << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ═════════
//  DISPLAY HEADER
// ═════════

void displayHeader() {
    clearScreen();
    printLine('*');
    cout << "*" << setw(63) << "*" << "\n";
    cout << "*       HOME STRUCTURE PLANNER  v2.0                          *\n";
    cout << "*       Plan | Visualize | Optimize                           *\n";
    cout << "*" << setw(63) << "*" << "\n";
    printLine('*');
}

// ═════════
//  OWNER INFO
// ═══════════

void getOwnerInfo(HomePlan& plan) {
    printSection("OWNER INFORMATION");
    cin.ignore();
    cout << "  Owner Name     : "; getline(cin, plan.ownerName);
    cout << "  Plot Location  : "; getline(cin, plan.plotLocation);
}

// ═════════════
//  PLOT INFO
// ═══════════

void getPlotInfo(HomePlan& plan) {
    printSection("PLOT DIMENSIONS");
    plan.plotLength = getPositiveFloat("  Plot Length (ft) : ", 10.0f);
    plan.plotWidth  = getPositiveFloat("  Plot Width  (ft) : ", 10.0f);
    plan.plotArea   = plan.plotLength * plan.plotWidth;
    plan.usableArea = plan.plotArea * (1.0f - WALL_DEDUCTION);
}

void displayPlotInfo(const HomePlan& plan) {
    printSection("PLOT SUMMARY");
    cout << fixed << setprecision(2);
    cout << "  Owner          : " << plan.ownerName     << "\n";
    cout << "  Location       : " << plan.plotLocation  << "\n";
    cout << "  Plot Dimension : " << plan.plotLength << " ft x " << plan.plotWidth << " ft\n";
    cout << "  Total Area     : " << plan.plotArea       << " sq ft\n";
    cout << "  Usable Area    : " << plan.usableArea     << " sq ft  (90%)\n";
    cout << "  Wall Reserve   : " << plan.plotArea * WALL_DEDUCTION << " sq ft  (10%)\n";
}

// ════════════
//  TEMPLATES
// ══════════

void showTemplates() {
    printSection("PREDEFINED HOME TEMPLATES");
    cout << "  1. 1 BHK   - Bedroom + Hall + Kitchen + Bathroom\n";
    cout << "  2. 2 BHK   - 2 Bedrooms + Hall + Kitchen + 2 Bathrooms\n";
    cout << "  3. 3 BHK   - 3 Bedrooms + Hall + Kitchen + 3 Bathrooms + Balcony\n";
    cout << "  4. Villa   - 4 Beds + 2 Halls + Kitchen + 4 Baths + Balcony + Garage\n";
    cout << "  5. Custom  - Define your own rooms from scratch\n";
}

void applyTemplate(HomePlan& plan, int choice) {
    plan.rooms.clear();

    auto add = [&](string name, float len, float wid, string type) {
        Room r;
        r.name   = name;
        r.length = len;
        r.width  = wid;
        r.area   = len * wid;
        r.type   = type;
        plan.rooms.push_back(r);
    };

    switch (choice) {
        case 1:
            add("Bedroom",   12, 10, "bedroom");
            add("Hall",      14, 10, "hall");
            add("Kitchen",   10,  8, "kitchen");
            add("Bathroom",   6,  5, "bathroom");
            break;
        case 2:
            add("Bedroom 1", 12, 10, "bedroom");
            add("Bedroom 2", 12, 10, "bedroom");
            add("Hall",      16, 12, "hall");
            add("Kitchen",   10,  8, "kitchen");
            add("Bathroom 1", 6,  5, "bathroom");
            add("Bathroom 2", 6,  5, "bathroom");
            break;
        case 3:
            add("Master Bedroom", 14, 12, "bedroom");
            add("Bedroom 2",      12, 10, "bedroom");
            add("Bedroom 3",      12, 10, "bedroom");
            add("Hall",           18, 14, "hall");
            add("Kitchen",        12,  9, "kitchen");
            add("Bathroom 1",      6,  5, "bathroom");
            add("Bathroom 2",      6,  5, "bathroom");
            add("Bathroom 3",      6,  5, "bathroom");
            add("Balcony",        10,  4, "other");
            break;
        case 4:
            add("Master Bedroom", 16, 14, "bedroom");
            add("Bedroom 2",      13, 11, "bedroom");
            add("Bedroom 3",      13, 11, "bedroom");
            add("Bedroom 4",      12, 10, "bedroom");
            add("Living Hall",    20, 16, "hall");
            add("Dining Hall",    16, 12, "hall");
            add("Kitchen",        14, 10, "kitchen");
            add("Bathroom 1",      7,  6, "bathroom");
            add("Bathroom 2",      7,  6, "bathroom");
            add("Bathroom 3",      7,  6, "bathroom");
            add("Bathroom 4",      7,  6, "bathroom");
            add("Balcony",        12,  5, "other");
            add("Garage",         20, 10, "other");
            break;
    }
}

// ════════════
//  CUSTOM ROOMS
// ════════════

void addCustomRooms(HomePlan& plan) {
    int n = getIntInRange("\n  How many rooms to add? (1-20): ", 1, 20);
    cin.ignore();

    for (int i = 0; i < n; i++) {
        Room r;
        cout << "\n  --- Room " << i + 1 << " ---\n";
        cout << "  Name   (e.g. Bedroom): "; getline(cin, r.name);

        r.length = getPositiveFloat("  Length (ft)        : ", 5.0f);
        r.width  = getPositiveFloat("  Width  (ft)        : ", 4.0f);
        r.area   = r.length * r.width;

        if (r.area < MIN_ROOM_SIZE)
            cout << "  [!] Warning: Room area " << r.area << " sq ft is below recommended minimum (" << MIN_ROOM_SIZE << " sq ft)\n";

        r.type = "other";
        plan.rooms.push_back(r);
    }
}

// ═════════════
//  EDIT / DELETE ROOMS  (NEW FEATURE)
// ════════════

void listRoomsShort(const HomePlan& plan) {
    cout << "\n  No.  Room Name            Area\n";
    printLine('-', 45);
    for (int i = 0; i < (int)plan.rooms.size(); i++) {
        cout << "  " << setw(3) << i+1 << ". "
             << left << setw(20) << plan.rooms[i].name
             << right << setw(6) << plan.rooms[i].area << " sq ft\n";
    }
    printLine('-', 45);
}

void editRooms(HomePlan& plan) {
    if (plan.rooms.empty()) { cout << "  No rooms to edit.\n"; return; }

    while (true) {
        printSection("EDIT / DELETE ROOMS");
        listRoomsShort(plan);
        cout << "  0. Done editing\n";

        int choice = getIntInRange("  Select room to edit/delete (0 to exit): ", 0, plan.rooms.size());
        if (choice == 0) break;

        Room& r = plan.rooms[choice - 1];
        cout << "\n  1. Edit room\n  2. Delete room\n";
        int action = getIntInRange("  Choose: ", 1, 2);

        if (action == 2) {
            cout << "  Deleted: " << r.name << "\n";
            plan.rooms.erase(plan.rooms.begin() + choice - 1);
        } else {
            cin.ignore();
            cout << "  New Name   [" << r.name   << "]: ";
            string nm; getline(cin, nm);
            if (!nm.empty()) r.name = nm;

            float nl = getPositiveFloat("  New Length (ft) [" + to_string((int)r.length) + "]: ", 5.0f);
            float nw = getPositiveFloat("  New Width  (ft) [" + to_string((int)r.width)  + "]: ", 4.0f);
            r.length = nl; r.width = nw; r.area = nl * nw;
            cout << "  Updated successfully!\n";
        }
    }
}

// ════════════
//  CALCULATE
// ══════════════
void calculateUsage(HomePlan& plan) {
    plan.totalUsed = 0;
    for (auto& r : plan.rooms)
        plan.totalUsed += r.area;
    plan.remaining = plan.usableArea - plan.totalUsed;
}
// ══════════════════
//  ROOM TABLE
// ═══════════

void displayRoomTable(const HomePlan& plan) {
    printSection("ROOM LAYOUT TABLE");
    cout << fixed << setprecision(2);
    cout << left
         << setw(22) << "Structure"
         << setw(13) << "Length(ft)"
         << setw(12) << "Width(ft)"
         << setw(14) << "Area(sqft)"
         << setw(10) << "% Plot"
         << "\n";
    printLine('=');

    for (auto& r : plan.rooms) {
        float pct = (r.area / plan.plotArea) * 100.0f;
        cout << left
             << setw(22) << r.name
             << setw(13) << r.length
             << setw(12) << r.width
             << setw(14) << r.area
             << setw(8)  << pct << "%"
             << "\n";
    }

    printLine('=');
    cout << left
         << setw(22) << "TOTAL USED"
         << setw(13) << "-"
         << setw(12) << "-"
         << setw(14) << plan.totalUsed
         << setw(8)  << (plan.totalUsed / plan.plotArea * 100) << "%"
         << "\n";
    printLine();
}

// ══════════
//  PROGRESS BAR  (NEW FEATURE)
// ═══════
void displayProgressBar(float used, float total, int width = 40) {
    float pct = min((used / total) * 100.0f, 100.0f);
    int   filled = (int)(pct / 100.0f * width);

    cout << "  [";
    for (int i = 0; i < width; i++)
        cout << (i < filled ? "#" : "-");
    cout << "] " << fixed << setprecision(1) << pct << "%\n";
}

// ═══════════
//  SUMMARY
// ═══════════

void displaySummary(const HomePlan& plan) {
    float usagePct = (plan.totalUsed / plan.usableArea) * 100.0f;

    printSection("USAGE SUMMARY");
    cout << fixed << setprecision(2);
    cout << "  Total Plot Area   : " << plan.plotArea   << " sq ft\n";
    cout << "  Usable Area       : " << plan.usableArea << " sq ft\n";
    cout << "  Total Area Used   : " << plan.totalUsed  << " sq ft\n";
    cout << "  Remaining Area    : " << plan.remaining  << " sq ft\n\n";

    cout << "  Space Utilization:\n  ";
    displayProgressBar(plan.totalUsed, plan.usableArea);

    printSection("STATUS");
    if (plan.remaining < 0) {
        cout << "  [!!] OVER LIMIT: Rooms exceed usable area by "
             << abs(plan.remaining) << " sq ft!\n";
        cout << "       Please reduce room sizes or remove some rooms.\n";
    } else if (usagePct >= 90) {
        cout << "  [**] EXCELLENT! Plot is very well utilized (" << usagePct << "%)\n";
    } else if (usagePct >= 70) {
        cout << "  [OK] Good utilization (" << usagePct << "%). "
             << plan.remaining << " sq ft free for garden/parking.\n";
    } else {
        cout << "  [>>] Low utilization (" << usagePct << "%). "
             << plan.remaining << " sq ft available for extra rooms.\n";
    }
}

// ══════════════════════════════
//  ROOM TYPE SUMMARY  (NEW FEATURE)
// ═════════════════════════════════

void displayRoomTypeSummary(const HomePlan& plan) {
    int beds = 0, baths = 0, halls = 0, kitchens = 0, others = 0;
    for (auto& r : plan.rooms) {
        if      (r.type == "bedroom")  beds++;
        else if (r.type == "bathroom") baths++;
        else if (r.type == "hall")     halls++;
        else if (r.type == "kitchen")  kitchens++;
        else                           others++;
    }
    printSection("ROOM TYPE SUMMARY");
    cout << "  Bedrooms   : " << beds     << "\n";
    cout << "  Bathrooms  : " << baths    << "\n";
    cout << "  Halls      : " << halls    << "\n";
    cout << "  Kitchens   : " << kitchens << "\n";
    cout << "  Others     : " << others   << "\n";
    cout << "  Total      : " << plan.rooms.size() << " rooms\n";
}

// ══════════════════════════
//  COST ESTIMATOR  (NEW FEATURE)
// ═══════════════════════════

void displayCostEstimate(const HomePlan& plan) {
    float costLow  = plan.totalUsed * COST_PER_SQFT_LO;
    float costHigh = plan.totalUsed * COST_PER_SQFT_HI;

    printSection("CONSTRUCTION COST ESTIMATE (India)");
    cout << fixed << setprecision(0);
    cout << "  Built-up Area     : " << plan.totalUsed << " sq ft\n";
    cout << "  Rate (Budget)     : Rs. " << COST_PER_SQFT_LO << " per sq ft\n";
    cout << "  Rate (Premium)    : Rs. " << COST_PER_SQFT_HI << " per sq ft\n\n";
    cout << "  Budget Estimate   : Rs. " << costLow  << "\n";
    cout << "  Premium Estimate  : Rs. " << costHigh << "\n";
    cout << "\n  * Excludes land cost, interior, and finishing charges.\n";
}

// ══════════════════════
//  VASTU CHECK  (NEW FEATURE)
// ══════════════════════════

void vastuCheck(const HomePlan& plan) {
    printSection("VASTU SHASTRA TIPS");
    bool hasKitchen = false, hasMaster = false;
    for (auto& r : plan.rooms) {
        if (r.type == "kitchen") hasKitchen = true;
        if (r.name.find("Master") != string::npos) hasMaster = true;
    }
    cout << "  [*] Main entrance  : Prefer North or East direction\n";
    if (hasKitchen)
        cout << "  [*] Kitchen        : Best placed in South-East (Agni corner)\n";
    if (hasMaster)
        cout << "  [*] Master Bedroom : Ideal in South-West for stability\n";
    cout << "  [*] Pooja Room     : Place in North-East corner\n";
    cout << "  [*] Bathrooms      : Avoid North-East corner\n";
    cout << "  [*] Staircase      : Best in South or West\n";
}

// ═════════════
//  SUGGESTIONS
// ═════════════

void suggestExtraSpace(const HomePlan& plan) {
    if (plan.remaining <= 0) return;

    printSection("SUGGESTIONS FOR REMAINING " + to_string((int)plan.remaining) + " sq ft");
    if (plan.remaining >= 200) cout << "  [+] Add a Garden / Lawn          (~200 sq ft)\n";
    if (plan.remaining >= 150) cout << "  [+] Add a Parking Space           (~150 sq ft)\n";
    if (plan.remaining >= 100) cout << "  [+] Add a Store Room              (~100 sq ft)\n";
    if (plan.remaining >= 80)  cout << "  [+] Add a Pooja Room              ( ~80 sq ft)\n";
    if (plan.remaining >= 50)  cout << "  [+] Add a Utility/Washing Area    ( ~50 sq ft)\n";
    if (plan.remaining >= 30)  cout << "  [+] Add a Passage/Corridor        ( ~30 sq ft)\n";
}

// ════════════════════════
//  SAVE REPORT TO FILE  (NEW FEATURE)
// ═════════════════════

void saveReport(const HomePlan& plan) {
    string filename = "home_report_" + plan.ownerName + ".txt";
    // Replace spaces in filename
    replace(filename.begin(), filename.end(), ' ', '_');

    // Redirect to file by reopening cout is complex;
    // instead write directly using ofstream pattern via freopen
    FILE* f = freopen(filename.c_str(), "w", stdout);
    if (!f) { cerr << "Could not save file.\n"; return; }

    cout << "HOME STRUCTURE PLANNER - REPORT\n";
    cout << "================================\n";
    cout << "Owner    : " << plan.ownerName    << "\n";
    cout << "Location : " << plan.plotLocation << "\n\n";

    cout << fixed << setprecision(2);
    cout << "Plot     : " << plan.plotLength << " x " << plan.plotWidth << " ft\n";
    cout << "Total    : " << plan.plotArea   << " sq ft\n";
    cout << "Usable   : " << plan.usableArea << " sq ft\n\n";

    cout << left << setw(22)<<"Room" << setw(10)<<"L(ft)" << setw(10)<<"W(ft)" << setw(12)<<"Area" << "\n";
    cout << string(54,'-') << "\n";
    for (auto& r : plan.rooms)
        cout << left << setw(22)<<r.name << setw(10)<<r.length << setw(10)<<r.width << setw(12)<<r.area << "\n";
    cout << string(54,'-') << "\n";
    cout << "Total Used : " << plan.totalUsed << " sq ft\n";
    cout << "Remaining  : " << plan.remaining << " sq ft\n";
    cout << "Efficiency : " << (plan.totalUsed/plan.usableArea*100) << "%\n\n";
    cout << "Cost (Budget)  : Rs. " << plan.totalUsed * COST_PER_SQFT_LO << "\n";
    cout << "Cost (Premium) : Rs. " << plan.totalUsed * COST_PER_SQFT_HI << "\n";

    freopen("/dev/tty", "w", stdout); 

    cout << "\n  [*] Report saved to: " << filename << "\n";
}

// ═══════════════════
//  MAIN MENU  (NEW FEATURE)
// ═════════════════

void showMainMenu() {
    printSection("MAIN MENU");
    cout << "  1. View Room Table\n";
    cout << "  2. View Usage Summary\n";
    cout << "  3. View Room Type Summary\n";
    cout << "  4. View Cost Estimate\n";
    cout << "  5. View Vastu Tips\n";
    cout << "  6. View Suggestions\n";
    cout << "  7. Edit / Delete Rooms\n";
    cout << "  8. Add More Rooms\n";
    cout << "  9. Save Report to File\n";
    cout << "  0. Exit\n";
}

// ════════
//  MAIN
// ════════

int main() {
    HomePlan plan;

    displayHeader();
    getOwnerInfo(plan);
    getPlotInfo(plan);
    displayPlotInfo(plan);
    pause();

    // Template selection
    showTemplates();
    int tmpl = getIntInRange("\n  Choose an option (1-5): ", 1, 5);

    if (tmpl >= 1 && tmpl <= 4) {
        applyTemplate(plan, tmpl);
        cout << "\n  Template applied with " << plan.rooms.size() << " rooms.\n";

        char more;
        cout << "  Add more custom rooms? (y/n): ";
        cin >> more;
        if (more == 'y' || more == 'Y')
            addCustomRooms(plan);
    } else {
        addCustomRooms(plan);
    }

    // Main loop
    int option = -1;
    while (option != 0) {
        calculateUsage(plan);
        displayHeader();
        displayPlotInfo(plan);
        showMainMenu();

        option = getIntInRange("\n  Your choice: ", 0, 9);

        switch (option) {
            case 1: displayRoomTable(plan);       pause(); break;
            case 2: displaySummary(plan);         pause(); break;
            case 3: displayRoomTypeSummary(plan); pause(); break;
            case 4: displayCostEstimate(plan);    pause(); break;
            case 5: vastuCheck(plan);             pause(); break;
            case 6: suggestExtraSpace(plan);      pause(); break;
            case 7: editRooms(plan);              break;
            case 8: addCustomRooms(plan);         break;
            case 9: saveReport(plan);             pause(); break;
            case 0:
                printLine('*');
                cout << "*         PLANNING COMPLETE! BEST OF LUCK!              *\n";
                printLine('*');
                break;
        }
    }

    return 0;
}