public class Demo1 {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        int n=1000;
        int [][]a=new int[n][n];
        int [][]b=new int[n][n];
        long startTime;
        long endTime;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                a[i][j]=i+j;
                b[i][j]=i+j;        
            }
        }
        startTime=System.currentTimeMillis();
        calMatrix1(a,b,n);
        endTime=System.currentTimeMillis(); 
        System.out.println(endTime-startTime);
        
        
        startTime=System.currentTimeMillis();
        calMatrix2(a,b,n);
        endTime=System.currentTimeMillis(); 
        System.out.println(endTime-startTime);
    }
    
    public static int[][] calMatrix1(int a[][],int b[][],int n){
        int [][]c=new int[n][n];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    c[i][j]+=a[i][k]*b[k][j];
                }
            }
        }
        return c;
    }
    public static int[][] calMatrix2(int a[][],int b[][],int n){
        int [][]c=new int[n][n];
        int B=500;
        for(int jj=0;jj<n;jj=jj+B){
            for(int kk=0;kk<n;kk=kk+B){
                for(int i=0;i<n;i++){
                    for(int j=jj;j<min(kk+B,n);j=j+1){
                        int r=0;
                        for(int k=kk;k<min(kk+B,n);k=k+1){
                            r=r+a[i][k]*b[k][j];
                        }
                        c[i][j]=r;
                    }
                }
            }
        }
        return c;
    }
    public static int min(int a,int b){
        if(a>b) return b;
        else return a;
    }
}
