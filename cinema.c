#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

// Fonksiyon Prototipleri
void exit_program();
void employeeMenu();
void setRezervation(char* username);
void seeTheSallon();
void seeMyReservations(char* username);
int menu();
void print_film_name_pretty(char* film_name);
void generate_salon_filename(const char* film_name, char* filename_buffer);
void load_salon_for_film(const char* film_name);
void save_salon_for_film(const char* film_name);

// Film isimlerini güzel bir şekilde yazdırmak için yardımcı fonksiyon
void print_film_name_pretty(char* film_name) {
    char temp_name[100];
    strcpy(temp_name, film_name);
    for (int i = 0; temp_name[i] != '\0'; i++) {
        if (temp_name[i] == '_') {
            temp_name[i] = ' ';
        }
    }
    printf("%s", temp_name);
}


int salon[5][10] = {0}; // Global salon dizisi, o anki aktif salonu tutar

// --- Yeni Salon Yönetim Fonksiyonları ---

// "Film_Adi_salon.txt" gibi bir dosya adı oluşturur
void generate_salon_filename(const char* film_name, char* filename_buffer) {
    strcpy(filename_buffer, film_name);
    strcat(filename_buffer, "_salon.txt");
}

// Belirli bir filmin salonunu global 'salon' dizisine yükler
void load_salon_for_film(const char* film_name) {
    char salon_filename[150];
    generate_salon_filename(film_name, salon_filename);

    FILE *loadFile = fopen(salon_filename, "r");
    if (loadFile != NULL) {
        // Dosya mevcut, yükleniyor
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                if (fscanf(loadFile, "%d", &salon[i][j]) != 1) {
                    // Olası dosya bozulmasını sıfırlayarak ele al
                    salon[i][j] = 0;
                }
            }
        }
        fclose(loadFile);
    } else {
        // Dosya mevcut değil, bu yüzden salonu boş olarak başlat
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                salon[i][j] = 0;
            }
        }
    }
}

// Global 'salon' dizisini belirli bir filmin dosyasına kaydeder
void save_salon_for_film(const char* film_name) {
    char salon_filename[150];
    generate_salon_filename(film_name, salon_filename);

    FILE *saveFile = fopen(salon_filename, "w");
    if (saveFile != NULL) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                fprintf(saveFile, "%d ", salon[i][j]);
            }
            fprintf(saveFile, "\n");
        }
        fclose(saveFile);
    } else {
        printf("Hata: Salon durumu kaydedilemedi!\n");
    }
}

// --- Yeni Salon Yönetim Fonksiyonları Sonu ---

void exit_program(){
    // programdan çıkış işlemleri
    printf("Programdan çıkılıyor...\n");
    return;
}

void employeeMenu(){

    FILE *employees = fopen("employees.txt", "a+"); // ekleme ve okuma için aç
    if (employees == NULL)
    {
        printf("Error opening employees file.\n");
        return;
    }
    
    char employe_Username[50]; 
    char employe_Password[50];

    char fileemploye_Username[50];
    char fileemploye_Password[50]; 

    int employe_choice ;

    printf("Yeni çalışan Kaydı yapmak için 1'e basınız:\n");
    printf("Mevcut çalışan girişi için 2'e basınız:\n");
    scanf("%d", &employe_choice);
    
    if (employe_choice == 1)
    {
        printf("Kullanıcı Adı Oluşturun: ");
        scanf("%s", employe_Username);
        printf("Şifre Oluşturun: ");
        scanf("%s", employe_Password);
        fprintf(employees, "%s %s\n", employe_Username, employe_Password);
        printf("Çalışan başarıyla kaydedildi.\n");
    }
    else if (employe_choice == 2)
    {
        printf("Kullanıcı Adı: ");
        scanf("%s", employe_Username);  
        printf("Şifre: ");
        scanf("%s", employe_Password);

        int login_success = 0;
        rewind(employees); // okumak için dosyanın başına git
        while (fscanf(employees, "%s %s", fileemploye_Username, fileemploye_Password) != EOF)
        {
            if (strcmp(employe_Username, fileemploye_Username) == 0 && strcmp(employe_Password, fileemploye_Password) == 0)
            {
                login_success = 1;
                break;
            }
        }

        if (login_success)
        {
            int employe_logged_choice = 0;
            printf("Hoşgeldiniz, Çalışan %s!\n", employe_Username);
            
            do {
                printf("1. Salonu Gör\n");
                printf("2. Film Menüsü\n");
                printf("3. Çıkış\n");
                printf("Seçiminizi yapın: ");
                scanf("%d", &employe_logged_choice);

                if (employe_logged_choice == 1)
                {
                    FILE *films = fopen("films.txt", "r");
                    if (films == NULL) {
                        printf("Henüz gösterimde film yok.\n");
                        continue;
                    }

                    printf("\n--- Hangi Filmin Salonunu Görmek İstersiniz? ---\n");
                    char film_name[100];
                    int film_price;
                    int film_count = 0;
                    while (fscanf(films, "%s %d", film_name, &film_price) != EOF)
                    {
                        printf("- ");
                        print_film_name_pretty(film_name);
                        printf("\n");
                        film_count++;
                    }
                    fclose(films);

                    if (film_count == 0) {
                        printf("Henüz gösterimde film yok.\n");
                        continue;
                    }
                    printf("------------------------------------------------\n");

                    char chosen_film[100];
                    printf("Filmin adını girin (boşluk yerine _ kullanın): ");
                    scanf("%s", chosen_film);

                    load_salon_for_film(chosen_film);
                    seeTheSallon();
                }
                else if (employe_logged_choice == 2)
                { 
                    FILE *films = fopen("films.txt", "a+");
                     if (films == NULL)
                    {
                        printf("Error opening films file.\n");
                        continue;
                    }

                    char film_name[100];
                    int employe_add_film_choice, film_price;

                    printf("Film Ekleme Menüsü\n");
                    printf("1. Film Ekle\n");
                    printf("2. Film Sil\n");
                    printf("3. Film Listele\n");
                    printf("Seçiminizi yapın: ");
                    scanf("%d", &employe_add_film_choice);

                    if (employe_add_film_choice == 1)
                    {
                        printf("Eklenecek filmin adını girin (boşluk yerine _ kullanın): ");
                        scanf("%s", film_name);
                        printf("Filmin fiyatını girin: ");
                        scanf("%d", &film_price);

                        fprintf(films, "%s %d\n", film_name, film_price);
                        printf("Film başarıyla eklendi.\n");
                    }
                    else if (employe_add_film_choice == 2)
                    {
                        // Hangisinin silineceğini sormadan önce film listesini göster
                        rewind(films);
                        printf("\n--- Vizyondaki Filmler ---\n");
                        int film_count = 0;
                        while (fscanf(films, "%s %d", film_name, &film_price) != EOF)
                        {
                            printf("- ");
                            print_film_name_pretty(film_name);
                            printf(" (%d TL)\n", film_price);
                            film_count++;
                        }
                        printf("---------------------------\n");

                        if (film_count == 0){
                            printf("Silinecek film bulunmuyor.\n");
                        } else {
                            char film_to_delete[100];
                            printf("Silmek istediğiniz filmin adını girin (boşluk yerine _ kullanın): ");
                            scanf("%s", film_to_delete);

                            FILE *temp_file = fopen("temp_films.txt", "w");
                            if(temp_file == NULL){
                                printf("Error creating temporary file.\n");
                                fclose(films);
                                continue;
                            }

                            rewind(films);
                            int found = 0;
                            while (fscanf(films, "%s %d", film_name, &film_price) != EOF)
                            {
                                if (strcmp(film_name, film_to_delete) != 0)
                                {
                                    fprintf(temp_file, "%s %d\n", film_name, film_price);
                                } else {
                                    found = 1;
                                }
                            }
                            
                            fclose(films);
                            fclose(temp_file);

                            if(found){
                                remove("films.txt");
                                rename("temp_films.txt", "films.txt");
                                printf("Film başarıyla silindi.\n");
                            } else {
                                remove("temp_films.txt");
                                printf("Film bulunamadı.\n");
                            }
                            films = fopen("films.txt", "a+"); // gelecekteki işlemler için yeniden aç
                        }
                    }
                    else if (employe_add_film_choice == 3)
                    {
                        rewind(films);
                        printf("\n--- Vizyondaki Filmler ---\n");
                        int count = 0;
                        while (fscanf(films, "%s %d", film_name, &film_price) != EOF)
                        {
                            printf("- ");
                            print_film_name_pretty(film_name);
                            printf(" (%d TL)\n", film_price);
                            count++;
                        }
                         printf("---------------------------\n");
                        if (count == 0){
                            printf("Henüz film eklenmemiş.\n");
                        }
                    }
                    fclose(films);
                }
                else if (employe_logged_choice == 3)
                {
                    printf("Çıkış yapılıyor...\n");
                }
                else
                {
                    printf("Geçersiz seçim!\n");
                }
            } while (employe_logged_choice != 3);
        } else {
            printf("Giriş başarısız! Kullanıcı adı veya şifre hatalı.\n");
        }
    }
    fclose(employees);
}

void seeMyReservations(char* username) {
    FILE *reservationsFile = fopen("reservations.txt", "r");
    if (reservationsFile == NULL) {
        printf("\nHenüz hiç rezervasyon yapılmamış.\n");
        return;
    }

    char file_username[50];
    char film_name[100];
    char row;
    int col;
    int user_reservations_found = 0;

    printf("\n--- %s Adlı Kullanıcının Rezervasyonları ---\n", username);
    while (fscanf(reservationsFile, "%s %s %c%d", file_username, film_name, &row, &col) != EOF) {
        if (strcmp(username, file_username) == 0) {
            printf("Film: ");
            print_film_name_pretty(film_name);
            printf(", Koltuk: %c%d\n", row, col);
            user_reservations_found = 1;
        }
    }

    if (!user_reservations_found) {
        printf("Hiç rezervasyonunuz bulunamadı.\n");
    }
    printf("------------------------------------------\n");

    fclose(reservationsFile);
}

void setRezervation(char* username){

    FILE *films = fopen("films.txt", "r");
    if (films == NULL)
    {
        printf("Henüz gösterimde film yok. Lütfen daha sonra tekrar deneyin.\n");
        return;
    }

    printf("\n--- Vizyondaki Filmler ---\n");
    char film_name[100];
    int film_price;
    int film_count = 0;
    while (fscanf(films, "%s %d", film_name, &film_price) != EOF)
    {
        printf("- ");
        print_film_name_pretty(film_name);
        printf(" (%d TL)\n", film_price);
        film_count++;
    }
    fclose(films);

    if (film_count == 0) {
        printf("Henüz gösterimde film yok. Lütfen daha sonra tekrar deneyin.\n");
        return;
    }
    printf("---------------------------\n\n");

    char chosen_film[100];
    printf("İzlemek istediğiniz filmin adını girin (boşluk yerine _ kullanın): ");
    scanf("%s", chosen_film);

    // Seçilen film için salonu yükle
    load_salon_for_film(chosen_film);

    seeTheSallon(); // Seçilen film için salon düzenini göster

    char row;
    int col;
    
    printf("\nRezervasyon yapmak için satır ve sütun numarası girin:\n");
    printf("Satır (A-E): ");
    scanf(" %c", &row);
    printf("Sütun (1-10): ");
    scanf("%d", &col);

    int rowIndex = row - 'A';
    int colIndex = col - 1;
    if (rowIndex < 0 || rowIndex >= 5 || colIndex < 0 || colIndex >= 10)
    {
        printf("Geçersiz satır veya sütun numarası!\n");
        return;
    }
    if (salon[rowIndex][colIndex] == 1)
    {
        printf("Bu koltuk dolu lütfen başka bir yer seçiniz.\n");
    }else
    {
        salon[rowIndex][colIndex] = 1;
        printf("Rezervasyon başarıyla yapıldı: Film: ");
        print_film_name_pretty(chosen_film);
        printf(", Koltuk: %c%d\n", row, col);

        // Güncellenmiş salon durumunu filmin özel dosyasına kaydet
        save_salon_for_film(chosen_film);
        printf("Sistem güncellendi.\n");

        // reservations.txt dosyasına kaydet
        FILE *reservationsFile = fopen("reservations.txt", "a");
        if (reservationsFile != NULL) {
            fprintf(reservationsFile, "%s %s %c%d\n", username, chosen_film, row, col);
            fclose(reservationsFile);
        }
        
    }
    
    
}

void seeTheSallon(){
    printf("Salonlarımız :\n");

    printf("  1 2 3 4 5 6 7 8 9 10\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%c ", 'A' + i);
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", salon[i][j]);
        }
        printf("\n");
    }
    
}

int menu() {

    int entrance_choice;

    printf("\n--- Sinema Rezervasyon Sistemi ---\n");
    printf("1. Giriş Yap\n");
    printf("2. Üye Ol\n");
    printf("3. Çalışan Girişi\n");
    printf("4. Çıkış\n");
    printf("Seçiminizi Yapın: ");

    scanf("%d", &entrance_choice);

    if (entrance_choice == 1)
    {
        char username[50];
        char password[50];
        char fileusername[50];
        char filepassword[50];

        printf("Kullanıcı Adı: ");
        scanf("%s", username);  
        printf("Şifre: ");
        scanf("%s", password);

        FILE *checkUser = fopen("customers.txt", "r");
        int login_success = 0;
        if (checkUser != NULL)
        {
            while (fscanf(checkUser, "%s %s", fileusername, filepassword) != EOF)
            {
                if (strcmp(username, fileusername) == 0 && strcmp(password, filepassword) == 0)
                {
                    login_success = 1;
                    break;
                }
            }
            fclose(checkUser);
        }

        if (login_success == 1)
        {
            printf("Giriş başarılı! Hoşgeldiniz, %s!\n", username);
            int user_choice = 0;
            do {
                printf("\n1. Salonu Gör\n");
                printf("2. Rezervasyon Yap\n");
                printf("3. Rezervasyonlarımı Gör\n");
                printf("4. Çıkış\n");
                printf("Seçiminizi yapın: ");
                scanf("%d", &user_choice);
                
                switch(user_choice) {
                    case 1:
                        {
                            FILE *films = fopen("films.txt", "r");
                            if (films == NULL) {
                                printf("Henüz gösterimde film yok.\n");
                                break;
                            }

                            printf("\n--- Hangi Filmin Salonunu Görmek İstersiniz? ---\n");
                            char film_name[100];
                            int film_price;
                            int film_count = 0;
                            while (fscanf(films, "%s %d", film_name, &film_price) != EOF)
                            {
                                printf("- ");
                                print_film_name_pretty(film_name);
                                printf("\n");
                                film_count++;
                            }
                            fclose(films);

                            if (film_count == 0) {
                                printf("Henüz gösterimde film yok.\n");
                                break;
                            }
                             printf("------------------------------------------------\n");

                            char chosen_film[100];
                            printf("Filmin adını girin (boşluk yerine _ kullanın): ");
                            scanf("%s", chosen_film);

                            load_salon_for_film(chosen_film);
                            seeTheSallon();
                        }
                        break;
                    case 2:
                        setRezervation(username);
                        break;
                    case 3:
                        seeMyReservations(username);
                        break;
                    case 4:
                        printf("Oturum kapatılıyor...\n");
                        break;
                    default:
                        printf("Geçersiz seçim!\n");
                        break;
                }
            } while (user_choice != 4);
        }
        else
        {
            printf("Giriş başarısız! Kullanıcı adı veya şifre hatalı.\n");
        }
        return 0; // Ana döngüye devam et
    }
    else if (entrance_choice == 2)
    {
        char username[50];
        char password[50];
        FILE *customers = fopen("customers.txt", "a");
        if (customers == NULL){
            printf("Error opening customers file.\n");
            return 0;
        }

        printf("Kullanıcı Adı Oluşturun: ");
        scanf("%s", username);
        printf("Şifre Oluşturun: ");
        scanf("%s", password);

        fprintf(customers, "%s %s\n", username, password);
        printf("Üyelik başarıyla oluşturuldu!\n");
        fclose(customers);
        return 0; // Ana döngüye devam et
    }
    else if (entrance_choice == 3)
    {
        employeeMenu();
        return 0; // Ana döngüye devam et
    }
    else if (entrance_choice == 4)
    {
        return 1; // Ana döngüden çıkmak için sinyal ver
    }
    else
    {
        printf("Geçersiz seçim!\n");
        return 0; // Ana döngüye devam et
    }
}

int main() {
    SetConsoleOutputCP(65001);
    
    while (menu() != 1) {
        // Bu döngü, menu() 1 döndürene kadar devam edecek (kullanıcı çıkmayı seçti)
        printf("\n"); // Menü tekrar gösterilmeden önce daha iyi formatlama için yeni bir satır ekle
    }
    
    printf("Programdan çıkılıyor...\n");
    return 0;
}