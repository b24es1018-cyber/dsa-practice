class Solution {
public:
int maxElement(vector<vector<int>>& arr, int col) {
          int n = arr.size();
          int max_val = INT_MIN;
          int index = -1;
  
          // Iterate through each row to find the maximum element 
          // in the particular column
          for (int i = 0; i < n; i++) {
              if (arr[i][col] > max_val) {
                  max_val = arr[i][col];
                  index = i;
              }
          }
          return index;
      }
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size();     
          int m = mat[0].size();  
  
          // Initialize the lower and upper bounds for binary search
          int low = 0;           
          int high = m - 1;      
  
          // Perform binary search on columns
          while (low <= high) {
              int mid = (low + high) / 2;
  
              // Find the index of the row with the maximum element 
              // in the middle column
              int row = maxElement(mat, mid);
  
              // Determine the elements to the left and right of 
              // the middle element in the found row
              int left = mid - 1 >= 0 ? mat[row][mid - 1] : INT_MIN;
              int right = mid + 1 < m ? mat[row][mid + 1] : INT_MIN;
  
              // Check if the middle element is greater than its neighbors
              if (mat[row][mid] > left && mat[row][mid] > right) {
                  return {row, mid};
              } 
              else if (left > mat[row][mid]) {
                  high = mid - 1;
              } 
              else {
                  low = mid + 1;
              }
          }
  
          // Return {-1, -1} if no peak element is found
          return {-1, -1};
      }
    
};