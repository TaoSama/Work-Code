#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string defaultManagerPwd = "manager";
const string defaultChefPwd = "chef";

void clr() {
#ifdef linux
    cout << "\033[H\033[J";
#endif // linux
#ifdef _WIN32
    system("cls");
#endif // WIN32
}

enum User {
    MANAGER,
    CHEF,
    CUSTOMER
};

class Material {
public:
    Material(const string& name, const double& price):
        name(name), price(price) {}
    string getName() const {
        return name;
    }
    double getPrice() const {
        return price;
    }
    void setName(const string& rName) {
        name = rName;
    }
    void setPrice(const double& rPrice) {
        price = rPrice;
    }
    bool operator==(const Material& rMaterial) const {
        return name == rMaterial.getName();
    }

private:
    string name;
    double price;
};

class Dish {
public:
    Dish(const int& id, const string& name,
         const vector<Material>& materials):
        id(id), name(name), materials(materials) {
        price = 0;
        for(int i = 0; i < materials.size(); ++i)
            price += materials[i].getPrice();
    }
    bool operator==(const Dish& rDish) const {
        return id == rDish.id || name == rDish.name;
    }

    int id;
    double price;
    string name;
    vector<Material> materials;
};

class Customer {
public:
    Customer(const int& id, const string& name) :
        id(id), name(name) {
        order.clear();
        fee = 0;
    }
    string getName() const {
        return name;
    }
    int getID() const {
        return id;
    }
    bool orderDish(const Dish& dish) {
        if(find(order.begin(), order.end(), dish) != order.end())
            return false;
        order.push_back(dish);
        fee += dish.price;
        return true;
    }
    double checkOut() {
        return fee;
    }
    bool operator==(const Customer& r) const {
        return id == r.getID() && name == r.getName();
    }
private:
    int id;
    string name;
    vector<Dish> order;
    double fee;
};

class MaterialController {
public:
    MaterialController() {
        rawMaterials.clear();
    }
    Material getMaterial(const string& name) {
        Material m(name, -1);
        return *find(rawMaterials.begin(), rawMaterials.end(), m);
    }
    bool search(const string& name) {
        Material m(name, -1.0);
        return find(rawMaterials.begin(), rawMaterials.end(), m)
               != rawMaterials.end();
    }
    bool add(const Material& m) {
        if(find(rawMaterials.begin(), rawMaterials.end(), m)
                != rawMaterials.end()) return false;
        rawMaterials.push_back(m);
        return true;
    }
    bool del(const Material& m) {
        vector<Material>::iterator p =
            find(rawMaterials.begin(), rawMaterials.end(), m);
        if(p == rawMaterials.end()) return false;
        rawMaterials.erase(p);
        return true;
    }
    bool modify(const Material& m, const Material& n) {
        vector<Material>::iterator p =
            find(rawMaterials.begin(), rawMaterials.end(), m);
        if(p == rawMaterials.end()) return false;
        if(search(n.getName())) return false;
        *p = n;
        return true;
    }
    vector<Material> get() {
        return rawMaterials;
    }
private:
    vector<Material> rawMaterials;
} materialController;

class CustomerController {
public:
    CustomerController() {
        customerList.clear();
    }
    bool add(const string& name) {
        Customer m(customerList.size(), name);
        customerList.push_back(m);
        return true;
    }
    bool search(const Customer& m) {
        return find(customerList.begin(), customerList.end(), m)
               != customerList.end();
    }
    Customer getCustomer(const Customer& m) {
        return *find(customerList.begin(), customerList.end(), m);
    }
    bool del(const Customer& m) {
        vector<Customer>::iterator p =
            find(customerList.begin(), customerList.end(), m);
        if(p == customerList.end()) return false;
        customerList.erase(p);
        return true;
    }
    bool modify(const Customer& m) {
        vector<Customer>::iterator p =
            find(customerList.begin(), customerList.end(), m);
        if(p == customerList.end()) return false;
        *p = m;
        return true;
    }
    vector<Customer> get() {
        return customerList;
    }
private:
    vector<Customer> customerList;
} customerController;

class MenuController {
public:
    MenuController() {
        menu.clear();
    }
    bool search(const int& id, const string& name) {
        Dish dish(id, name, vector<Material>());
        return find(menu.begin(), menu.end(), dish)
               != menu.end();
    }
    Dish getDish(const int& id, const string& name) {
        Dish dish(id, name, vector<Material>());
        return *find(menu.begin(), menu.end(), dish);
    }
    vector<Dish> get() {
        return menu;
    }
    bool add(const Dish& m) {
        vector<Dish>::iterator p = find(menu.begin(), menu.end(), m);
        if(p != menu.end()) return false;
        menu.push_back(m);
        return true;
    }
    bool del(const Dish& m) {
        vector<Dish>::iterator p = find(menu.begin(), menu.end(), m);
        if(p == menu.end()) return false;
        menu.erase(p);
        return true;
    }
    bool modify(const Dish& m, const Dish& n) {
        vector<Dish>::iterator p = find(menu.begin(), menu.end(), m);
        if(p == menu.end()) return false;
        if(search(n.id, n.name)) return false;
        *p = n;
        return true;
    }
private:
    vector<Dish> menu;
} menuController;

int getChoice(int l, int r) {
    printf("Enter a single number or <q> to quit: ");

    static char choice[100];
    scanf("%s", choice); //read

    if(choice[0] == 'q' && !choice[1]) return -2; //for quit

    int length = strlen(choice);
    if(length > 2) return -1; //length error

    for(int i = 0; choice[i]; ++i)
        if(!isdigit(choice[i])) return -1; //invalid

    int x = atoi(choice);
    if(x < l || x > r) return -1; //out of bound

    return x; //valid choice
}

void mainMenu() {
    puts("------Welcome to Restaurant Management System------");
    puts("loading...\n");
    puts("Identification verifying, 1 for Manger, 2 for Chef, 3 for Customer.");
}

void pwdPrompt(const string& key) {
    static char pwd[100];
    do {
        printf("Enter password: ");
        scanf("%s", pwd);
        if(string(pwd) == key) break;
        else puts("Wrong password\n");
    } while(true);
}

void seeMaterial(User type) {
    int choice = -1;
    bool toClr = true;
    do {
        if(toClr) {
            clr();
            puts("------Update Material------");
            puts("loading...\n");

            puts("1. Browse");
            puts("2. Search");
            if(type == MANAGER) {
                puts("3. Add");
                puts("4. Modify");
                puts("5. Delete");
            }
        }

        toClr = true;
        choice = getChoice(1, 5);

        static char name[100];
        static double price;
        if(choice == -1 ||
                type != MANAGER && choice >= 3 && choice <= 5) {
            toClr = false;
            puts("Invalid input!\n");
            continue;
        } else if(choice == 1) {
            vector<Material> v = materialController.get();
            if(v.size()) {
                printf("%-10s %-10s\n", "Name", "Price");
                for(int i = 0; i < v.size(); ++i) {
                    Material& m = v[i];
                    printf("%-10s %-10.3f\n", m.getName().c_str(), m.getPrice());
                }
            } else puts("Raw Materials is empty");
        } else if(choice == 2) {
            printf("Please enter the name of material: ");
            scanf("%s", name);
            if(!materialController.search(name)) puts("No such material");
            else {
                printf("%-10s %-10s\n", "Name", "Price");
                Material m = materialController.getMaterial(name);
                printf("%-10s %-10.3f\n", m.getName().c_str(), m.getPrice());
            }
        } else if(choice == 3) {
            printf("Please enter the name and price of material: ");
            scanf("%s%lf", name, &price);
            if(!materialController.add(Material(name, price)))
                puts("The material has already existed");
            else puts("The material is added successfully");
        } else if(choice == 4) {
            printf("Please enter the old name of material: ");
            scanf("%s", name);
            Material o(name, -1);
            printf("Please enter the new name and price of material: ");
            scanf("%s%lf", name, &price);
            Material n(name, price);
            if(!materialController.modify(o, n))
                puts("No such material");
            else puts("The material is modified successfully");
        } else if(choice == 5) {
            printf("Please enter the name of material: ");
            scanf("%s", name);
            if(!materialController.del(Material(name, price)))
                puts("No such material");
            else puts("The material is deleted successfully");
        }
        if(choice != -2) {
            printf("Press any key to continue...");
            getchar(); getchar();
        }
    } while(choice != -2);
}

void seeMenu(User type) {
    int choice = -1;
    bool toClr = true;
    do {
        if(toClr) {
            clr();
            puts("------Update Menu------");
            puts("loading...\n");

            puts("1. Browse");
            puts("2. Search");
            puts("3. Modify");
            if(type == MANAGER) {
                puts("4. Add");
                puts("5. Delete");
            }
        }

        toClr = true;
        choice = getChoice(1, 5);

        static char name[100];
        static int id;
        if(choice == -1 ||
                type != MANAGER && choice >= 4 && choice <= 5) {
            toClr = false;
            puts("Invalid input!\n");
            continue;
        } else if(choice == 1) {
            vector<Dish> v = menuController.get();
            if(v.size()) {
                printf("%-10s %-10s %-10s\n", "ID", "Name", "Price");
                for(int i = 0; i < v.size(); ++i) {
                    Dish& m = v[i];
                    printf("%-10d %-10s %-10.3f\n", m.id, m.name.c_str(), m.price);
                }
            } else puts("Menu is empty");
        } else if(choice == 2) {
            printf("Please enter the id and name of dish: ");
            scanf("%d%s", &id, name);
            if(!menuController.search(id, name)) puts("No such dish");
            else {
                printf("%-10s %-10s %-10s\n", "ID", "Name", "Price");
                Dish m = menuController.getDish(id, name);
                printf("%-10d %-10s %-10.3f\n", m.id, m.name.c_str(), m.price);
            }
        } else if(choice == 3) {
            printf("Please enter the old id and name of dish: ");
            scanf("%d%s", &id, name);
            if(!menuController.search(id, name)) puts("No such dish");
            else {
                printf("Please enter the new id and name of dish: ");
                Dish o(id, name, vector<Material>());
                scanf("%d%s", &id, name);
                if(menuController.search(id, name))
                    puts("The dish has already existed");
                else {
                    static char mName[100];
                    int num;
                    printf("Please enter the number of the materials: \n");
                    scanf("%d", &num);
                    vector<Material> v;
                    bool legal = true;
                    while(num--) {
                        scanf("%s", mName);
                        if(!materialController.search(mName)) {
                            legal = false;
                            break;
                        }
                        v.push_back(materialController.getMaterial(mName));
                    }
                    if(!legal) puts("Illegal dish");
                    else {
                        menuController.modify(o, Dish(id, name, v));
                        puts("The dish is modified successfully");
                    }
                }
            }
        } else if(choice == 4) {
            printf("Please enter the id and name of dish: ");
            scanf("%d%s", &id, name);
            if(menuController.search(id, name))
                puts("The dish has already existed");
            else {
                static char mName[100];
                int num;
                printf("Please enter the number of the materials: \n");
                scanf("%d", &num);
                vector<Material> v;
                bool legal = true;
                while(num--) {
                    scanf("%s", mName);
                    if(!materialController.search(mName)) {
                        legal = false;
                        break;
                    }
                    v.push_back(materialController.getMaterial(mName));
                }
                if(!legal) puts("Illegal dish");
                else {
                    menuController.add(Dish(id, name, v));
                    puts("The dish is added successfully");
                }
            }
        } else if(choice == 5) {
            printf("Please enter the id and name of dish: ");
            scanf("%d%s", &id, name);
            if(!menuController.del(Dish(id, name, vector<Material>())))
                puts("No such dish");
            else puts("The dish is deleted successfully");
        }
        if(choice != -2) {
            printf("Press any key to continue...");
            getchar(); getchar();
        }
    } while(choice != -2);
}

void seeCustomer() {
    int choice = -1;
    bool toClr = true;
    do {
        if(toClr) {
            clr();
            puts("------Update Customers------");
            puts("loading...\n");

            puts("1. Browse");
            puts("2. Add");
            puts("3. Delete");
        }

        toClr = true;
        choice = getChoice(1, 3);

        static char name[100];
        static int id;
        if(choice == -1) {
            toClr = false;
            puts("Invalid input!\n");
            continue;
        } else if(choice == 1) {
            vector<Customer> v = customerController.get();
            if(v.size()) {
                printf("%-10s %-10s\n", "ID", "Name");
                for(int i = 0; i < v.size(); ++i) {
                    Customer& m = v[i];
                    printf("%-10d %-10s\n", m.getID(), m.getName().c_str());
                }
            } else puts("There is no customers");
        } else if(choice == 2) {
            printf("Please enter the name of customer: ");
            scanf("%s", name);
            if(customerController.add(name))
                puts("The customer is added successfully");
        } else if(choice == 3) {
            printf("Please enter the id and name of customer: ");
            scanf("%d%s", &id, name);
            if(!customerController.del(Customer(id, name))) puts("No such customer");
            else puts("The customer is deleted successfully");
        }
        if(choice != -2) {
            printf("Press any key to continue...");
            getchar(); getchar();
        }
    } while(choice != -2);
}

void thirdMenu(int cmd, User type) {
    if(cmd == 1) seeMaterial(type);
    else if(cmd == 2) seeMenu(type);
    else seeCustomer();
}

void secondMenu(User type) {
    int choice = -1;
    bool toClr = true;
    do {
        if(toClr) {
            clr();
            puts("------Update Information------");
            puts("loading...\n");

            printf("1. Raw Materials\n");
            printf("2. Menu\n");
            if(type == MANAGER) printf("3. Customer\n");
        }

        toClr = true;
        choice = getChoice(1, 3);

        if(type != MANAGER && choice == 3 ||
                choice == -1) {
            toClr = false;
            puts("Invalid input!\n");
            continue;
        } else if(choice == 1) thirdMenu(1, type);
        else if(choice == 2) thirdMenu(2, type);
        else if(choice == 3) thirdMenu(3, type);
        if(choice != -2) {
            printf("Press any key to continue...");
            getchar(); getchar();
        }

    } while(choice != -2);
}

void customerOp() {
    int choice = -1;
    bool toClr = true;
    Customer cur(-1, "NULL");
    do {
        if(toClr) {
            clr();
            puts("------Customer Interface------");
            puts("loading...\n");

            printf("0. Login\n");
            printf("1. Browse Menu\n");
            printf("2. Order Dish\n");
            printf("3. Check Out\n");
        }

        toClr = true;
        choice = getChoice(0, 3);

        static char name[100];
        static int id;
        if(choice == -1) {
            toClr = false;
            puts("Invalid input!\n");
            continue;
        } else if(choice == 0) {
            printf("Please enter your id and name: ");
            scanf("%d%s", &id, name);
            if(!customerController.search(Customer(id, name))) {
                puts("Please contact manager to add your information");
            } else {
                cur = customerController.getCustomer(Customer(id, name));
                puts("You have logged in successfully");
            }
        } else if(choice == 1) {
            vector<Dish> v = menuController.get();
            if(v.size()) {
                printf("%-10s %-10s %-10s\n", "ID", "Name", "Price");
                for(int i = 0; i < v.size(); ++i) {
                    Dish& m = v[i];
                    printf("%-10d %-10s %-10.3f\n", m.id, m.name.c_str(), m.price);
                }
            } else puts("Menu is empty");
        } else if(choice == 2) {
            if(cur.getName() == "NULL") {
                printf("Please login first\n");
            } else {
                printf("Please enter the id and name of dish: ");
                scanf("%d%s", &id, name);
                if(!menuController.search(id, name)) puts("No such dish");
                else {
                    Dish m = menuController.getDish(id, name);
                    cur.orderDish(m);
                    puts("You have ordered the dish successfully");
                }
            }
        } else if(choice == 3) {
            if(cur.getName() == "NULL") {
                printf("Please login first\n");
            } else {
                double cost = cur.checkOut();
                printf("The total fee is %.3f\n", cost);
                customerController.del(cur);
                cur = Customer(-1, "NULL");
                puts("You have logged out and checked out successfully");
            }
        }
        if(choice != -2) {
            printf("Press any key to continue...");
            getchar(); getchar();
        }

    } while(choice != -2);
}

void displayMenu(int cmd) {
    if(cmd == 0) mainMenu();
    else if(cmd == 1) {
        pwdPrompt(defaultManagerPwd);
        secondMenu(MANAGER);
    } else if(cmd == 2) {
        pwdPrompt(defaultChefPwd);
        secondMenu(CHEF);
    } else {
        customerOp();
    }
}

int main() {

    int choice = -1;
    bool toClr = true;
    do {
        if(toClr) {
            clr();
            displayMenu(0); //main menu
        }
        choice = getChoice(1, 3);

        toClr = true;
        if(choice == 1) displayMenu(1); //Manager
        else if(choice == 2) displayMenu(2); //Chef
        else if(choice == 3) displayMenu(3); //Custom
        else if(choice == -1) {
            toClr = false;
            puts("Invalid input!\n");
            continue;
        }
        if(choice != -2) {
            printf("Press any key to continue...");
            getchar(); getchar();
        }

    } while(choice != -2);

    return 0;
}
