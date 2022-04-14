

//      Functors
// ====================
// Objects that are able to execute a function call and therefore treated as such

class insertationSort{
    private:
        const int m_val;
    public:
        insertationSort(int n) : m_val{n}{}
        void operator()(int arr[]){
            int i, k, temp;

            for(i=1 ; i < m_val ; i++){
                k = arr[i];
                temp = i - 1;
                while(temp >= 0 && arr[temp] > k){
                    arr[temp + 1] = arr[temp];
                    temp = temp - 1;
                    arr[temp +1 ] = k;
                }
            }
        }
};


#include <iostream>
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main(int argv, char* argn[]){

    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    auto fn = insertationSort(n);
    fn(arr);

    printArray(arr, n);
    



    return 0;
}