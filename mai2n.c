#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#define NUM_NODES 7 // A(0), B(1), C(2), D(3), E(4), F(5), G(6)
#define INF INT_MAX

char nodeNames[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};   //isimlendirme

// Tablodaki Hash Erisim Maliyetleri [cite: 1, 3, 4, 5, 6, 7, 10, 11, 12, 13, 14, 15, 16, 17]
// G(6) dugumunun degeri kullanicidan alinan isme gore guncellenecek.
int hashCosts[NUM_NODES] = {1, 3, 2, 4, 2, 1, 0}; 

// --- 2. GOREV: KENDI STACK YAPIMIZ ---
typedef struct {
    int items[NUM_NODES];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
} 

void push(Stack* s, int value) {    //Son Giren Ýlk Çýkar
    s->items[++(s->top)] = value;
    printf("Stack PUSH: %c dugumu eklendi.\n", nodeNames[value]);
}

int pop(Stack* s) {     //eleman ekleme 
    if (s->top == -1) return -1;
    int val = s->items[(s->top)--];
    printf("Stack POP: %c dugumu cikarildi.\n", nodeNames[val]);   //Yýðýn kontrol DFS(öncelikli girdi)
    return val;  //stackten alýnan veriyi 
}

// --- ADJACENCY LIST (KOMSULUK LISTESI) YAPISI ---
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct Graph {
    AdjListNode* array[NUM_NODES];
} Graph;

AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph() {
    int i; 
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (i = 0; i < NUM_NODES; ++i)
        graph->array[i] = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
}

void updateEdge(Graph* graph, int src, int dest, int newWeight) {
    AdjListNode* temp = graph->array[src];
    while (temp != NULL) {
        if (temp->dest == dest) {
            temp->weight = newWeight;
            return;
        }
        temp = temp->next;
    }
}

// --- 1. ve 4. GOREV: DIJKSTRA ALGORITMASI ---
void dijkstra(Graph* graph, int src, int target, int isDynamicTest) {
    int dist[NUM_NODES];
    int visited[NUM_NODES];
    int parent[NUM_NODES];
    
    // Performans metrikleri
    int iterations = 0;
    int comparisons = 0;
    int totalHashCost = 0; // 4. Gorev icin eklendi
    
    int i, count, v, u, min, curr, nodeIndex; 
    clock_t start_time = clock();
    double time_spent;

    for (i = 0; i < NUM_NODES; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (count = 0; count < NUM_NODES - 1; count++) {
        iterations++;
        min = INF;
        u = -1;

        for (v = 0; v < NUM_NODES; v++) {
            comparisons++;
            if (visited[v] == 0 && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        visited[u] = 1;

        AdjListNode* temp = graph->array[u];
        while (temp != NULL) {
            v = temp->dest;
            comparisons++;
            if (!visited[v] && dist[u] != INF && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
    
    time_spent = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    if(dist[target] == INF) {
        printf("Hedefe ulasilamiyor.\n");
        return;
    }

    printf("\n--- DIJKSTRA SONUCLARI ---\n");
    printf("Toplam Yol Maliyeti (A -> %c): %d\n", nodeNames[target], dist[target]);
    
    if(isDynamicTest) {
        printf("Iterasyon Sayisi: %d\n", iterations);
        printf("Karsilastirma Sayisi: %d\n", comparisons);
        printf("Calisma Suresi: %f saniye\n", time_spent);
    }

    printf("\n--- STACK ISLEMLERI (YOL GERI SARMA) ---\n");
    Stack pathStack;
    initStack(&pathStack);
    
    curr = target;
    while (curr != -1) {
        push(&pathStack, curr);
        curr = parent[curr];
    }
    
    printf("\nEn Kisa Yol Ziyaret Sirasi: ");
    while (pathStack.top != -1) {
        nodeIndex = pop(&pathStack);
        printf("%c ", nodeNames[nodeIndex]);
        totalHashCost += hashCosts[nodeIndex]; // Yoldaki dugumlerin hash maliyetlerini topluyoruz
        if(pathStack.top != -1) printf("-> ");
    }
    printf("\n");

    // 4. GOREV: SISTEM MALIYETI HESABI 
    printf("\n--- SISTEM MALIYETI (Gorev 4) ---\n");
    printf("Yol Uzerindeki Toplam Hash Maliyeti: %d\n", totalHashCost);
    printf("TOPLAM SISTEM MALIYETI (Yol + Hash): %d\n", dist[target] + totalHashCost);
}

int main() {
    Graph* graph = createGraph();
    char studentNo[20];
    char studentName[50];
    int firstDigit, lastDigit, len, gHashCost;

    // PDF'teki varsayilan yollari ekliyoruz
    addEdge(graph, 0, 1, 4);  // A -> B
    addEdge(graph, 0, 2, 2);  // A -> C
    addEdge(graph, 1, 2, 1);  // B -> C
    addEdge(graph, 1, 3, 2);  // B -> D
    addEdge(graph, 2, 3, 5);  // C -> D
    addEdge(graph, 2, 4, 10); // C -> E
    addEdge(graph, 3, 4, 3);  // D -> E
    addEdge(graph, 3, 5, 6);  // D -> F
    addEdge(graph, 4, 5, 1);  // E -> F

    // KULLANICI GIRISLERI
    printf("Ekipteki en kucuk ogrenci numarasini giriniz: ");
    scanf("%19s", studentNo); 
    
    printf("Ekipteki en kisa isme sahip ogrencinin adini giriniz: ");
    scanf("%49s", studentName);

    // Hesaplamalar
    firstDigit = studentNo[0] - '0'; 
    len = strlen(studentNo);
    lastDigit = studentNo[len - 1] - '0';
    gHashCost = strlen(studentName); 
    
    // G dugumunun Hash maliyetini guncelle [cite: 44]
    hashCosts[6] = gHashCost;

    if (lastDigit == 0) {
        lastDigit = 1;
        printf("\n[BILGI] Ogrenci numarasi 0 ile bittigi icin B -> G yol maliyeti 1 olarak guncellendi.\n");
    }

    printf("\nKurulan Yeni Yollar ve Maliyetler:\n");
    printf("D -> G yol maliyeti (Ilk Rakam): %d\n", firstDigit);
    printf("B -> G yol maliyeti (Son Rakam): %d\n", lastDigit);
    printf("G dugumu Hash Erisim Maliyeti (Isim Uzunlugu): %d\n", gHashCost);

    addEdge(graph, 3, 6, firstDigit); // D -> G
    addEdge(graph, 1, 6, lastDigit);  // B -> G

    printf("\n==========================================\n");
    printf("ILK DURUM: A'dan G'ye En Kisa Yol\n");
    printf("==========================================\n");
    dijkstra(graph, 0, 6, 0); 

    printf("\n\n==========================================\n");
    printf("DINAMIK DEGISIM: B -> D yolu 2 katina cikarildi!\n");
    printf("==========================================\n");
    
    updateEdge(graph, 1, 3, 4); 
    dijkstra(graph, 0, 6, 1); 

    printf("\n\n");
    system("pause"); 
    return 0;
}
