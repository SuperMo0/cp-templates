// todo: test with a problem and loog for better implementations (trie implemented with array)
class node
{
public:
    vector<node*> links;
    int en=INT_MAX;
    node()
    {
        links.resize(26);
        fill(links.begin(),links.end(),nullptr);
    }
};
class trie
{
public:
    node* root;
    node* crnt;
    trie()
    {
        root=new node();
        crnt=root;
    }
    void add(char c, int en)
    {
        if(crnt->links[c-'a']==NULL)
        {
            auto it=new node;
            crnt->links[c-'a']=it;
            crnt=crnt->links[c-'a'];
            if(en!=-1)
            {
                crnt->en=en;
            }
        }
        else
        {
            crnt=crnt->links[c-'a'];
        }
    }
    bool check(char c)
    {
        if(crnt->links[c-'a']!=nullptr)
        {
            crnt=crnt->links[c-'a'];
            return true;
        }
        else return false;
    }
    void reset()
    {
        crnt=root;
    }
};
