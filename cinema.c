#include <stdio.h>
#include <windows.h>

// Adım 1: Ekrana menüyü yazdır (Fonksiyon kullanabilirsin).
// Salonu Gör
// Rezervasyon Yap
// Kaydet ve Çık
// Adım 2: Kullanıcıdan seçim al (scanf).
// Adım 3: Seçime göre ilgili fonksiyona git:
// Seçenek 1 (Salonu Gör): İç içe for döngüleri ile diziyi ekrana yazdır. (Boşsa '0', Doluysa '1' veya 'X' göster).
// Seçenek 2 (Rezervasyon Yap):
// Kullanıcıdan "Satır" ve "Sütun" numarası iste.
// Kontrol Et: O koordinat dizide boş mu?
// Evetse: Dizideki o alanı "Dolu" olarak işaretle.
// Hayırsa: "Orası dolu!" diye hata ver.
// 3. Evre: Kapanış (Shutdown)
// Dosya Yazma: Matrisin (dizinin) son halini koltuklar.txt dosyasına satır satır yaz.
// Programı sonlandır.



int salon[5][10] = {0}; // salon dizisi
void exit(){
    // programdan çıkış işlemleri
    printf("Programdan çıkılıyor...\n");
    return;
}

void employeeMenu(){

    FILE *employees = fopen("employees.txt", "r+");
    if (employees == NULL)
    {
        employees = fopen("employees.txt", "w");
        fclose(employees);
        employees = fopen("employees.txt", "r+");
    }
    
    char employe_Username[50]; 
    char employe_Password[50];

    char fileemploye_Username[50];
    char fileemploye_Password[50]; 

    FILE *employeesRead = fopen("employees.txt", "r");

        int employe_choice ;

        printf("Yeni çalışan Kaydı yapmak için 1'e basınız :");
        printf("Mevcut çalışan girişi için 2'e basınız :");
        scanf("%d", employe_choice);
        if (employe_choice == 1)
        {

            printf("Kullanıcı Adı Oluşturun: ");
            scanf("%s", employe_Username);
            printf("Şifre Oluşturun: ");
            scanf("%s", employe_Password);
            fprintf(employees, "%s %s", employe_Username, employe_Password);
            fclose(employees);
            
        }else if (employe_choice == 2)
        {
            if (employeesRead == NULL)
            {
                printf("Henüz çalışan kaydı yok. Lütfen önce kayıt olun.\n");
            }

            while (fscanf(employeesRead, "%s %s", fileemploye_Username, fileemploye_Password) != EOF)
            {
                int employe_logged_choice = 0;
                printf("Hoşgeldiniz, Çalışan %s!\n", fileemploye_Username);
                printf("1. Salonu Gör\n");
                printf("2.Film Ekle\n");
                printf("3. Çık\n");
                printf("Seçiminizi yapın: ");
                scanf("%d", &employe_logged_choice);
                if (employe_logged_choice == 1)
                {
                    seeTheSallon();
                }
                else if (employe_logged_choice == 2)
                {
                    // FİLM EKLEME İŞLEMİ BURAYA EKLENECEK
                }
                else if (employe_logged_choice == 3)
                {
                    exit();
                }
                else
                {
                    printf("Geçersiz seçim!\n");
                }
            }        

        }

}

void setRezervation(){
    char row;
    int col;
    

    printf("Rezervasyon yapmak için satır ve sütun numarası girin:\n");
    printf("Satır (A-E): ");
    scanf(" %c", &row);
    printf("Sütun (1-10): \n");
    scanf("%d", &col);

    int rowIndex = row - 'A';
    int colIndex = col - 1;
    // Rezervasyon işlemi için (DOSYA YAZMA İŞLEMİ EKLENECEK)


    salon[rowIndex][colIndex] = 'X'; // Örnek olarak 'X' ile işaretleme
}

void seeTheSallon(){
    printf("Salonlarımız :\n");

    printf("  1 2 3 4 5 \n");
    for (int i = 0; i < 5; i++)
    {
        printf("%c ", 'A' + i);
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", salon[i][j]);
        }
        printf("\n");
    }
    
}

void menu() {
    FILE *customers = fopen("customers.txt", "r+");
    if (customers == NULL)
    {
        customers = fopen("customers.txt", "w");
        fclose(customers);
        customers = fopen("customers.txt", "r+");
    }

    int choice,entrance_choice;

    char username[50];
    char password[50];
    char fileusername[50];
    char filepassword[50];

    printf("Sinema Rezervasyon Sistemine Hoşgeldiniz!\n");
    printf("Giriş Yapmak İçin 1'e Basın: \n");
    printf("Üye Olmak İçin 2'ye Basın: \n");
    printf("Çalışan Girişi İçin 3'e Basın: \n");
    scanf("%d", &entrance_choice);
    if (entrance_choice == 1)
    {
        printf("Kullanıcı Adı: ");
        scanf("%s", username);  
        printf("Şifre: ");
        scanf("%s", password);

        // dosyadan alınan verilerle karşılaştırma yap (HENUZ YAPMADIN)
    }
    else if (entrance_choice == 2)
    {
        printf("Kullanıcı Adı Oluşturun: ");
        scanf("%s", username);
        printf("Şifre Oluşturun: ");
        scanf("%s", password);

        fprintf(customers, "%s %s", username, password);

        fclose(customers);
        // dosyaya yazma işlemi
    }
    else if (entrance_choice == 3)
    {
        employeeMenu();
    }
    else
    {
        printf("Geçersiz seçim!\n");
        return;
    }
    
    // printf("1. Salonu Gör\n");
    // printf("2. Rezervasyon Yap\n");
    // printf("3. Çık\n");
    // printf("Seçiminizi yapın: ");
    // scanf("%d", &choice);
    // if (choice == 1)
    // {
    //     seeTheSallon();
    // }
    // else if (choice == 2)
    // {
    //     setRezervation();
    // }
    // else if (choice == 3)
    // {
    //     exit();
    // }
    // else
    // {
    //     printf("Geçersiz seçim!\n");
    // }
}

int main() {
    SetConsoleOutputCP(65001);
    menu();
    return 0;
}