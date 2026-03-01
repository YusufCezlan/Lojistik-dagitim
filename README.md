# Dinamik Dijkstra Algoritması ve Sistem Maliyeti Hesaplayıcı

Bu proje, C dilinde geliştirilmiş, dinamik kenar ağırlıklarına ve düğüm (hash) maliyetlerine sahip bir yönlü graf üzerinde **Dijkstra En Kısa Yol Algoritmasını** uygulayan bir konsol uygulamasıdır. 

## 🚀 Özellikler

* **Dijkstra En Kısa Yol Algoritması:** Başlangıç düğümünden (A) hedef düğüme (G) olan optimum yolu hesaplar.
* **Özelleştirilmiş Veri Yapıları:**
  * Bellek verimliliği için graf temsilinde **Komşuluk Listesi (Adjacency List)** kullanılmıştır.
  * Algoritma sonucunda bulunan rotayı doğru sırayla (başlangıçtan hedefe) yazdırmak için özel bir **Yığın (Stack)** yapısı (LIFO) entegre edilmiştir.
* **Dinamik Graf Güncellemeleri:** Sisteme girilen kullanıcı verilerine (öğrenci numarası ve isim) göre belirli kenar ağırlıkları (B -> G ve D -> G) ve hedefin hash erişim maliyeti anlık olarak belirlenir.
* **Performans Metrikleri:** Graf üzerinde dinamik bir değişiklik yapıldığında (örneğin bir yolun maliyeti arttığında) algoritmanın iterasyon sayısı, karşılaştırma sayısı ve çalışma süresi (saniye cinsinden) analiz edilir.
* **Kapsamlı Maliyet Hesabı:** Standart yol maliyetine ek olarak, rotadaki her düğümün "Hash Erişim Maliyeti" de hesaplanarak toplam bir sistem maliyeti çıktısı üretilir.

## 🛠️ Kullanılan Teknolojiler

* **Dil:** C
* **Kütüphaneler:** `<stdio.h>`, `<stdlib.h>`, `<limits.h>`, `<time.h>`, `<string.h>`

## ⚙️ Nasıl Çalıştırılır?

Projeyi kendi bilgisayarınızda çalıştırmak için bir C derleyicisine (örneğin GCC) ihtiyacınız vardır. 
derleyiciye kodu kopyalamanız yeterlidir
