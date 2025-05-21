#include <iostream>
#include <iomanip>
using namespace std;

char pil;
int pilihan;

void menu()
{
    cout << setfill('=') << setw(33) << " " << endl;
    cout << setfill(' ') << setw(25) << "MANIS LEZAT BAKERY" << endl;
    cout << setfill('=') << setw(33) << " " << endl;
    cout << "1. Ambil Antrean" << endl;
    cout << "2. Layani Pembeli" << endl;
    cout << "3. Tampilkan Pesanan" << endl;
    cout << "4. Batalkan Pesanan" << endl;
    cout << "5. Riwayat Pesanan" << endl;
    cout << "6. Exit" << endl;
}

struct pesanan
{
    string nama;
    string jenisRoti;
    int totalHarga;
};

struct queue_stack
{
    pesanan data;
    queue_stack *next;
};
queue_stack *depan, *belakang;
queue_stack *awal = NULL, *top = NULL;

void buatAntrean()
{
    depan = NULL;
    belakang = NULL;
}

int queuekosong()
{
    return (depan == NULL);
}

bool stackkosong()
{
    return awal == NULL;
}

// enqueue (tambah antrean)
void tambahAntrean()
{
    string nama, jenisRoti;
    int totalHarga;

    cout << "Masukkan nama pembeli: "; getline(cin, nama);
    cout << "Masukkan jenis roti: "; getline(cin, jenisRoti);
    cout << "Masukkan total harga: "; cin >> totalHarga;
    
    queue_stack *NB = new queue_stack;
    NB->data.nama = nama;
    NB->data.jenisRoti = jenisRoti;
    NB->data.totalHarga = totalHarga;
    NB -> next = NULL;

    if (depan == NULL)
    {
        depan = NB;
    }
    else
    {
        belakang->next = NB;
    }
    belakang = NB;
    cout << "Pesanan ditambahkan ke antrean." << endl;
}

// layani pembeli
void pushRiwayat(pesanan p)
{
    queue_stack *NB = new queue_stack;
    NB->data = p;
    NB->next = NULL;

    if (awal == NULL) {
        awal = top = NB;
    } else {
        top->next = NB;
        top = NB;
    }
}

void layaniPembeli()
{
    if (queuekosong()) {
        cout << "Tidak ada antrean yang bisa dilayani!" << endl;
        return;
    }
    queue_stack *hapus = depan;
    pesanan p = hapus->data; // Simpan data sebelum dihapus

    depan = depan->next;
    if (depan == NULL) {
        belakang = NULL;
    }

    pushRiwayat(p);

    cout << "Pesanan telah dilayani: " << endl;
    cout << "Nama       : " << p.nama << endl;
    cout << "Jenis Roti : " << p.jenisRoti << endl;
    cout << "Total      : Rp" << p.totalHarga << endl;

    delete hapus;
}

// tampilkan pesanan
void tampilkanPesanan()
{
    queue_stack *bantu = depan;
    if (bantu == NULL) {
        cout << "Antrean kosong!" << endl;
        return;
    }

    cout << "Daftar Pesanan dalam Antrean: " << endl;
    int no = 1;
    while (bantu != NULL) {
        cout << no++ << ". Nama         : " << bantu->data.nama << endl;
        cout         << "   Jenis Roti   : " << bantu->data.jenisRoti << endl;
        cout         << "   Total Harga  : Rp" << bantu->data.totalHarga << endl;
        cout << setfill(' ') << setw(50) << " " << endl;
        bantu = bantu->next;
    }
}

// batalkan pesanan
void batalkanPesanan()
{
    if (queuekosong()) {
        cout << "Antrean kosong, tidak ada pesanan untuk dibatalkan." << endl;
        return;
    }

    //hanya satu pesanan di antrean
    if (depan == belakang) {
        cout << "Pesanan atas nama " << depan->data.nama << " dibatalkan." << endl;
        delete depan;
        depan = belakang = NULL;
        return;
    }
    else
    {
        //antrean lebih dari satu elemen
        queue_stack *bantu = depan;
        while (bantu->next != belakang) {
            bantu = bantu->next;
        }
        cout << "Pesanan atas nama " << belakang->data.nama << " dibatalkan." << endl;
        delete belakang;
        belakang = bantu;
        belakang->next = NULL;
    }
}

// riwayat pesanan
void riwayatPesanan()
{
    if (stackkosong()) {
        cout << "Riwayat pesanan masih kosong." << endl;
        return;
    }

    queue_stack *bantu = awal;
    cout << "Daftar Riwayat Pesanan: " << endl;
    int no = 1;
    while (bantu != NULL) {
        cout << no++ << ". Nama         : " << bantu->data.nama << endl;
        cout         << "   Jenis Roti   : " << bantu->data.jenisRoti << endl;
        cout         << "   Total Harga  : Rp" << bantu->data.totalHarga << endl;
        cout << setfill(' ') << setw(50) << " " << endl;
        bantu = bantu->next;
    }
}

int main()
{
    buatAntrean();
    do
    {
        menu();
        cout << setfill(' ') << setw(50) << " " << endl;
        cout << "Pilih Menu: "; cin >> pilihan;
        cout << setfill(' ') << setw(50) << " " << endl;
        switch (pilihan)
        {
        case 1:
            cin.ignore();
            tambahAntrean();
            break;
        case 2:
            layaniPembeli();
            break;
        case 3:
            tampilkanPesanan();
            break;
        case 4:
            batalkanPesanan();
            break;
        case 5:
            riwayatPesanan();
            break;
        case 6:
            cout << "TERIMA KASIH TELAH MENGGUNAKAN PROGRAM INI!" << endl;
            exit (0);
            break;
        
        default:
        cout << "Pilihan Anda tidak valid!" << endl;
            break;
        }
        cout << setfill(' ') << setw(50) << " " << endl;
        cout << "Apakah anda ingin kembali ke menu? (y/n) : "; cin >> pil;
        cout << setfill(' ') << setw(50) << " " << endl;
    } while (pil == 'y' || pil == 'Y');
    
}