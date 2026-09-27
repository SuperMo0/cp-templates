struct matrix
{
public:
    vector<vector<int>> a= {{0,0},{0,0}};
    matrix operator *(matrix b)
    {
        matrix c;
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<2; j++)
            {
                for(int k=0; k<2; k++)
                {
                    c.a[i][j]+=((a[i][k]*b.a[k][j])%mod);
                    c.a[i][j]%=mod;
                }
            }
        }
        return c;
    }
    vector<int> mulv(vector<int> v)
    {
        vector<int> ans(v.size());
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<2; j++)
            {
                ans[i]+=((a[i][j]*v[j])%mod);
                ans[i]%=mod;
            }
        }

        return ans;
    }

};
matrix fexp(matrix x,int y)
{
    matrix ans;
    ans.a={{1,0},{0,1} };
    while(y>0)
    {
        if(y&1ll)
        {
            ans=ans*x;
        }
        x=x*x;
        y/=2;
    }
    return ans;
}
