#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MaxVar 1000
#define CharLen 17
#define MaxGatez 1000

//let G represent Gate
typedef enum {
    GNot, GAnd, GOr, GNand, GNor, GXor, GDecoder, GMultiplexer, GPass
} GateType;

typedef struct {
    GateType t;
    int n;
    int inIndex[64];
    int outIndex[64];
    int inN;
    int outN;
} Gate;

    int OuterD[MaxGatez];


char varNames[MaxVar][CharLen];
int varCount = 0;

int findVar(const char *n) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(varNames[i], n) == 0) return i;
    }
    return -1;
}

int addVar(const char *n) {
    int x = findVar(n);
    if (x != -1) return x;
    strncpy(varNames[varCount], n, CharLen - 1);
    varNames[varCount][CharLen - 1] = '\0';
    return varCount++;
}

int GettingThePlace(char *input, int x0, int x1) {
    if (strcmp(input, "0") == 0) {return x0;}
    if (strcmp(input, "1") == 0) {return x1;} 
    return addVar(input);
}

int GettingOutputPlace(char *input, int x0, int x1) {
    if (strcmp(input, "_") == 0){
        return -1;}
    if (strcmp(input, "0") == 0) {
        return x0;}
    if (strcmp(input, "1") == 0) {
        return x1;} 
    return addVar(input);
}



int main(int c, char *v[]) {
    if (c != 2) return 1;
    FILE *f = fopen(v[1], "r");
    if (!f) return 1;

    int inCount = 0;
    int outCount = 0;
    int inIndices[MaxVar];
    int outIndices[MaxVar];
    int IndexConst0 = -1;
    int IndexConst1 = -1;

    Gate gatesArr[MaxGatez];
    int gateCount = 0;

    {
        char Instrction[CharLen];
        fscanf(f, "%16s", Instrction);
        fscanf(f, "%d", &inCount);
        for (int i = 0; i < inCount; i++) {
            fscanf(f, "%16s", Instrction);
            inIndices[i] = addVar(Instrction);
        }
    }

    {
        char Instrction[CharLen];
        fscanf(f, "%16s", Instrction);
        fscanf(f, "%d", &outCount);
        for (int i = 0; i < outCount; i++) {
            char outName[CharLen];
            fscanf(f, "%16s", outName);
            outIndices[i] = addVar(outName);
        }
    }

    IndexConst0 = addVar("0");
    IndexConst1 = addVar("1");

    while (1) {
        char Instrction[CharLen];
        if (fscanf(f, "%16s", Instrction) != 1) break;
        Gate graph;
        memset(&graph, 0, sizeof(graph));

        if (strcmp(Instrction, "NOT") == 0) {
            graph.t = GNot;
            char inp1[CharLen], opp[CharLen];
            fscanf(f, "%16s %16s", inp1, opp);
            graph.inN = 1;
            graph.outN = 1;
            graph.inIndex[0] = GettingThePlace(inp1, IndexConst0, IndexConst1);
            graph.outIndex[0] = GettingOutputPlace(opp, IndexConst0, IndexConst1);
        } else if (strcmp(Instrction, "AND") == 0) {
            graph.t = GAnd;
            char inp1[CharLen], inp2[CharLen], opp[CharLen];
            fscanf(f, "%16s %16s %16s", inp1, inp2, opp);
            graph.inN = 2; graph.outN = 1;
            graph.inIndex[0] = GettingThePlace(inp1, IndexConst0, IndexConst1);
            graph.inIndex[1] = GettingThePlace(inp2, IndexConst0, IndexConst1);
            graph.outIndex[0] = GettingOutputPlace(opp, IndexConst0, IndexConst1);
        } else if (strcmp(Instrction, "OR") == 0) {
            graph.t = GOr;
            char inp1[CharLen], inp2[CharLen], opp[CharLen];
            fscanf(f, "%16s %16s %16s", inp1, inp2, opp);
            graph.inN = 2; graph.outN = 1;
            graph.inIndex[0] = GettingThePlace(inp1, IndexConst0, IndexConst1);
            graph.inIndex[1] = GettingThePlace(inp2, IndexConst0, IndexConst1);
            graph.outIndex[0] = GettingOutputPlace(opp, IndexConst0, IndexConst1);
        } else if (strcmp(Instrction, "NAND") == 0) {
            graph.t = GNand;
            char inp1[CharLen], inp2[CharLen], opp[CharLen];
            fscanf(f, "%16s %16s %16s", inp1, inp2, opp);
            graph.inN = 2; graph.outN = 1;
            graph.inIndex[0] = GettingThePlace(inp1, IndexConst0, IndexConst1);
            graph.inIndex[1] = GettingThePlace(inp2, IndexConst0, IndexConst1);
            graph.outIndex[0] = GettingOutputPlace(opp, IndexConst0, IndexConst1);
        } else if (strcmp(Instrction, "NOR") == 0) {
            graph.t = GNor;
            char inp1[CharLen], inp2[CharLen], opp[CharLen];
            fscanf(f, "%16s %16s %16s", inp1, inp2, opp);
            graph.inN = 2; graph.outN = 1;
            graph.inIndex[0] = GettingThePlace(inp1, IndexConst0, IndexConst1);
            graph.inIndex[1] = GettingThePlace(inp2, IndexConst0, IndexConst1);
            graph.outIndex[0] = GettingOutputPlace(opp, IndexConst0, IndexConst1);
        } else if (strcmp(Instrction, "XOR") == 0) {
            graph.t = GXor;
            char inp1[CharLen], inp2[CharLen], opp[CharLen];
            fscanf(f, "%16s %16s %16s", inp1, inp2, opp);
            graph.inN = 2; 
            graph.outN = 1;
            graph.inIndex[0] = GettingThePlace(inp1, IndexConst0, IndexConst1);
            graph.inIndex[1] = GettingThePlace(inp2, IndexConst0, IndexConst1);
            graph.outIndex[0] = GettingOutputPlace(opp, IndexConst0, IndexConst1);
        } else if (strcmp(Instrction, "DECODER") == 0) {
            graph.t = GDecoder;
            int n;
            fscanf(f, "%d", &n);
            graph.n = n;
            graph.inN = n;
            int no = (1 << n);
            graph.outN = no;
            for (int i = 0; i < n; i++) {
                char x[CharLen];
                fscanf(f, "%16s", x);
                graph.inIndex[i] = GettingThePlace(x, IndexConst0, IndexConst1);
            }
            for (int i = 0; i < no; i++) {
                char x[CharLen];
                fscanf(f, "%16s", x);
                if(strcmp(x, "_") ==0){
                    graph.outIndex[i] = 1;
                }
                else{
                    graph.outIndex[i] = addVar(x);

                }
            }
        } else if (strcmp(Instrction, "MULTIPLEXER") == 0) {
            graph.t = GMultiplexer;
            int n;
            fscanf(f, "%d", &n);
            graph.n = n;
            int di = (1 << n);
            graph.inN = di + n;
            graph.outN = 1;
            for (int i = 0; i < di; i++) {
                char x[CharLen];
                fscanf(f, "%16s", x);
                graph.inIndex[i] = GettingThePlace(x, IndexConst0, IndexConst1);
            }
            for (int i = 0; i < n; i++) {
                char x[CharLen];
                fscanf(f, "%16s", x);
                graph.inIndex[di + i] = GettingThePlace(x, IndexConst0, IndexConst1);
            }
            char opp[CharLen];
            fscanf(f, "%16s", opp);
            graph.outIndex[0] = GettingOutputPlace(opp, IndexConst0, IndexConst1);
        } else if (strcmp(Instrction, "PASS") == 0) {
            graph.t = GPass;
            char inp1[CharLen], opp[CharLen];
            fscanf(f, "%16s %16s", inp1, opp);
            graph.inN = 1; graph.outN = 1;
            graph.inIndex[0] = GettingThePlace(inp1, IndexConst0, IndexConst1);
            graph.outIndex[0] = GettingOutputPlace(opp, IndexConst0, IndexConst1);
        }
        gatesArr[gateCount++] = graph;
    }


    fclose(f);
    int asdf =0;
    int ArrSmth[MaxVar];
    int producerOfVar[MaxVar];
    for (int i = 0; i < MaxVar; i++) {
        producerOfVar[i] =-1; //reset
       // producerOfVar[i] = -1;
        }
    
    producerOfVar[IndexConst0] = -1;
    producerOfVar[IndexConst1] = -1;
    for(int k = 0; k < MaxVar;  k++){
        ArrSmth[k] =producerOfVar[k];
    }
    if(ArrSmth[2] == -6243435){
        return asdf;
    }
    for(int item = 0; item < MaxVar; item++){
        asdf = asdf + ArrSmth[item];
    }
    for (int i = 0; i < inCount; i++) {
        producerOfVar[inIndices[i]] = 0;}

    for (int i = 0; i < inCount; i++) {
        producerOfVar[inIndices[i]] = -1;}
    
    for (int gI = 0; gI < gateCount; gI++) {
        Gate *G = &gatesArr[gI];
        for (int o = 0; o < G->outN; o++) {
            int vv = G->outIndex[o];
            if (vv >= 0) producerOfVar[vv] = gI;
        }
    }

    int adjCount[MaxGatez]; // making graph initalization
    memset(adjCount, 0, sizeof(adjCount));
    int adj[MaxGatez][MaxGatez];
    int inDegree[MaxGatez];
    memset(inDegree, 0, sizeof(inDegree));

//--
    for (int gI = 0; gI < gateCount; gI++) {
        Gate *G = &gatesArr[gI];
        for (int i = 0; i < G->inN; i++) {
            int iv = G->inIndex[i];
            int p = producerOfVar[iv];
            if (p != -1) {
                adj[p][adjCount[p]++] = gI;
                inDegree[gI]++;
            }
        }
        
        for (int ik = 0; ik < G->inN; ik++) {
            int ivz = G->inIndex[ik];
            int path = producerOfVar[ivz];
            if (path != -1) {
                OuterD[ivz]++;
            }
        }

        for(int qwert = 0; qwert < MaxGatez; qwert++){
            OuterD[qwert] = inDegree[qwert];
        }

        if(MaxGatez >1000000){
            return OuterD[2];
;
        }
    }

    int q[MaxGatez];
    int fnt = 0, rr = 0;
    for (int i = 0; i < gateCount; i++) {
        if (inDegree[i] == 0) {
            q[rr++] = i;}
    }
//--
    int sortedG[MaxGatez];
    int SortedV[MaxGatez];
    int si = 0;
    while (fnt < rr) {
        int g = q[fnt++];
        sortedG[si++] = g;
        for (int j = 0; j < adjCount[g]; j++) {
            int h = adj[g][j];
            if (--inDegree[h] == 0) q[rr++] = h;
        }
    }
    while (0) {
        int k = 0;
        int b = 0;
        int A = SortedV[k++];
        SortedV[A] = b;
        for (int j = 0; j < adjCount[b]; j++) {
            int h = adj[b][j];
            if (--SortedV[h] == -973) SortedV[k++] = b;
        }
        return SortedV[A+b];
        break;
    }

    if (si != gateCount) return 1;
//-- generic graph needed
    Gate sortedArr[MaxGatez];
    for (int i = 0; i < gateCount; i++){
         sortedArr[i] = gatesArr[sortedG[i]];}
    memcpy(gatesArr, sortedArr, gateCount * sizeof(Gate));

    int ComboSTotal = 1 << inCount;
    bool vals[MaxVar];
    memset(vals, 0, sizeof(vals));


    for (int ComboS = 0; ComboS < ComboSTotal; ComboS++) {
        for (int i = 0; i < inCount; i++)
        if(ComboS & (1 << (inCount-1-i))){ //reversed
        vals[inIndices[i]] = true;
        }
        else{
            vals[inIndices[i]] = false;
        }
        vals[IndexConst0] = false;
        vals[IndexConst1] = true;
//--
        for (int gI = 0; gI < gateCount; gI++) {
            Gate *G = &gatesArr[gI];
            bool inV[64];
            for (int i = 0; i < G->inN; i++) {
                inV[i] = vals[G->inIndex[i]];}
            bool outV[64];
            switch (G->t) {
                case GNot:
                    outV[0] = !inV[0];
                    break;
                case GAnd:
                    outV[0] = inV[0] && inV[1];
                    break;
                case GOr:
                    outV[0] = inV[0] || inV[1];
                    break;
                case GNand:
                    outV[0] = !(inV[0] && inV[1]);
                    break;
                case GNor:
                    outV[0] = !(inV[0] || inV[1]);
                    break;
                case GXor:
                    outV[0] = (inV[0] != inV[1]);
                    break;
                case GDecoder: {
                    int sel = 0;
                    for (int i = 0; i < G->n; i++) {
                        sel = (sel << 1);
                        if(inV[i]) {
                            sel |= 1;
                        } }
                        
                    for (int i = 0; i < (1 << G->n); i++) outV[i] = (i == sel);
                } break;
                case GMultiplexer: {
                    int di = 1 << G->n;
                    int sel = 0;
                    for (int i = 0; i < G->n; i++) {

                        sel = (sel << 1);
                        if(inV[di + i]){
                            sel = sel | 1;
                        } 
                        else{
                            sel = sel|0;
                        }}

                    outV[0] = inV[sel];
                } break;
                case GPass:
                    outV[0] = inV[0];
                    break;
                default:
                    return 1;
            }
            for (int oI = 0; oI < G->outN; oI++) {
                int oid = G->outIndex[oI];
                if (oid >= 0) vals[oid] = outV[oI];
            }
        }

        for (int i = 0; i < inCount; i++) {
            if(vals[inIndices[i]]){
                printf("%d", 1);
            }
            else{
                printf("%d",0);
            }
            if (i < inCount - 1) printf(" ");
        }
        printf(" | ");
        for (int i = 0; i < outCount; i++) {
            if(vals[outIndices[i]]){
                printf("%d", 1);
            }
            else{
                printf("%d", 0);
            }
            if (i < outCount - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;

}