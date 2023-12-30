#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define M_PI 3.14159265358979323846

// Şehir bilgileri
double latitudes[] = {37, 38.681, 39.75, 36.4018, 39.9237, 38.4189, 38.7312, 41.1828, 40.6532, 39.82, 38.6823, 39.7217, 41.3887, 36.8};
double longitudes[] = {35.3213, 39.2264, 39.5, 36.3498, 44.0459, 27.1287, 35.4787, 41.8183, 35.8339, 34.8044, 29.4082,43.0567, 33.7827, 34.6333};
char* cityNames[] = {"Adana", "Elazig", "Erzincan", "Hatay", "Igdir", "Izmir", "Kayseri", "Artvin", "Amasya", "Yozgat", "Usak", "Agri", "Kastamonu", "Mersin"};

// Fonksiyon prototipleri
double calculateDistance(double lat1, double lon1, double lat2, double lon2);
double calculateAverageSpeed(double distance, int travelTime);
int getSunSide(double departureHour, double arrivalHour);

int findCityIndex(char cityName[]);
void printCityList();

int main() {
    char departureCity[50], arrivalCity[50];
    double departureHour, arrivalHour;
    int departureIndex, arrivalIndex;

    while (1) {
        // Kullanıcıdan giriş al
        printf("\nAbfahrtsort: ");
        scanf("%s", departureCity);

        if (strcmp(departureCity, "exit") == 0) {
            printf("Das Programm wird beendet.\n");
            break;
        }

        printf("Zielort: ");
        scanf("%s", arrivalCity);

        printf("Abfahrtszeit: ");
        scanf("%lf", &departureHour);

        printf("Ankunftszeit: ");
        scanf("%lf", &arrivalHour);

        // Şehirler arası uzaklığı hesapla
        double distance = 0.0;
        departureIndex = findCityIndex(departureCity);
        arrivalIndex = findCityIndex(arrivalCity);

        // Eğer giriş yapılan şehirler listede yoksa kullanıcıya yeni bir şehir girmesini iste
        while (departureIndex == -1) {
            printf("Geben Sie einen anderen Abfahrtsort ein: ");
            scanf("%s", departureCity);
            departureIndex = findCityIndex(departureCity);
        }

        while (arrivalIndex == -1) {
            printf("Geben Sie einen anderen Zielort ein: ");
            scanf("%s", arrivalCity);
            arrivalIndex = findCityIndex(arrivalCity);
        }

        distance = calculateDistance(latitudes[departureIndex], longitudes[departureIndex], latitudes[arrivalIndex], longitudes[arrivalIndex]);

        // Ortalama hızı hesapla
        int travelTime = (int)(arrivalHour - departureHour);
        double averageSpeed = calculateAverageSpeed(distance, travelTime);

        // Güneşin hangi tarafta olduğunu belirle
        int sunSide = getSunSide(departureHour, arrivalHour);

        // Sonuçları ekrana yazdır
        printf("\nDistanz zu fahren: %.2lf km\n", distance);
        printf("Durchschnittliche Geschwindigkeit des Verkehrsmittels: %.2lf km/h\n", averageSpeed);

        if (sunSide == 0) {
            printf("Information: Die Sonne wird nicht scheinen, egal auf welcher Seite ich sitze, je nach Fahrtrichtung (rechts oder links).\n");
        } else {
            printf("Alternative: Die Seite, auf der die Sonne während der gesamten Fahrt am meisten sichtbar ist: %s\n", (sunSide == 1) ? "rechts" : "links");
        }

        // Kullanıcıya devam etmek isteyip istemediğini sor
        printf("\nWeitermachen? (ja/nein): ");
        char continueInput[5];
        scanf("%s", continueInput);

        if (strcmp(continueInput, "nein") == 0) {
            break;
        }
    }

    return 0;
}

// İki nokta arasındaki mesafeyi hesapla (Düz çizgi mesafesi)
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371; // Dünya yarıçapı (km)
    double dLat = (lat2 - lat1) * M_PI / 180;
    double dLon = (lon2 - lon1) * M_PI / 180;
    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1 * M_PI / 180) * cos(lat2 * M_PI / 180) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

// Ortalama hızı hesapla
double calculateAverageSpeed(double distance, int travelTime) {
    if (travelTime == 0) {
        return 0.0;
    }
    return distance / travelTime;
}

// Güneşin hangi tarafta olduğunu belirle
int getSunSide(double departureHour, double arrivalHour) {
    if (departureHour < 7 || arrivalHour > 19) {
        return 0; // Güneşin her iki tarafta da olmadığı durum
    } else if ((departureHour >= 7 && departureHour < 12) || (arrivalHour > 12 && arrivalHour <= 19)) {
        return 1; // Güneşin sağ tarafta olduğu durum
    } else {
        return 2; // Güneşin sol tarafta olduğu durum
    }
}

// Şehir isminin dizideki indeksini bul
int findCityIndex(char cityName[]) {
    for (int i = 0; i < sizeof(cityNames) / sizeof(cityNames[0]); i++) {
        if (strcmp(cityName, cityNames[i]) == 0) {
            return i;
        }
    }
    return -1; // Şehir bulunamadı
}

// Mevcut şehir listesini yazdır
void printCityList() {
    printf("Mevcut Sehirler:\n");
    for (int i = 0; i < sizeof(cityNames) / sizeof(cityNames[0]); i++) {
        printf("%s\n", cityNames[i]);
    }
}
