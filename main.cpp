#include <iostream>
#include <string>

int main() {
    int q = 7;
    float part_gev[q] = {25.2, 0.511, 0.105, 0.139, 0.493, 0.938, 3.097};
    std::string part_names[q] = {"Too high", "Electron", "Muon", "Pion", 
                                  "Kaon", "Proton", "J/psi meson"};
    int events_count[q] = {0};
    int events_amount;
    float event_E;
    float pogr = 0.05;
    float unknown[q] = {0};
    int unknown_count = 0;
    
    std::cout << "Сколько событий? ";
    std::cin >> events_amount;
    std::cout << "Вводите энергии:\n";
    
    for (int i = 0; i < events_amount; i++) {
        std::cin >> event_E;
        bool found = false;
        
        if (event_E > part_gev[0]) {
            events_count[0]++;
            std::cout << "Слишком много!\n";
            continue;
        }
        
        for (int j = 1; j < q; j++) {
            float lower = part_gev[j] * (1 - pogr);
            float upper = part_gev[j] * (1 + pogr);
            
            if (event_E >= lower && event_E <= upper) {
                events_count[j]++;
                std::cout << "Нашли: " << part_names[j] << "\n";
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << "Неизвестно\n";
            if (unknown_count < q) {
                unknown[unknown_count] = event_E;
                unknown_count++;
            }
        }
    }
    
    std::cout << "\n РЕЗУЛЬТАТЫ \n\n";
    
    for (int j = 1; j < q; j++) {
        std::cout << part_names[j] << ": " << events_count[j] << "\n";
    }
    
    std::cout << "\nСлишком много: " << events_count[0] << "\n";
    std::cout << "Неизвестно: " << unknown_count << "\n";
    
    if (unknown_count > 0) {
        std::cout << "\nНеизвестные энергии:\n";
        for (int i = 0; i < unknown_count; i++) {
            std::cout << unknown[i] << "\n";
        }
    }
    
    return 0;
}