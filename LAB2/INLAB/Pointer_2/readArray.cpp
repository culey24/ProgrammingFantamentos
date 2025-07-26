int** readArray()
{
   //TODO
   int** arr = new int*[10];
   for (int i = 0; i < 10; i++) {
       arr[i] = new int[10];
       for (int j = 0; j < 10; j++) {
           cin>>arr[i][j];
           if (arr[i][j] == 0) {
                for (int k = j + 1; k < 10; k++) {
                    arr[i][k] = 0;
                }
               break;
           }
       }
   }
   return arr;
}