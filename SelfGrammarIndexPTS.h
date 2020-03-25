//
// Created by alpachec on 20-09-18.
//

#ifndef IMPROVED_GRAMMAR_INDEX_SELFGRAMMARINDEXPTS_H
#define IMPROVED_GRAMMAR_INDEX_SELFGRAMMARINDEXPTS_H



#include "SelfGrammarIndexPT.h"




class SelfGrammarIndexPTS:public SelfGrammarIndexPT{

    protected:

    int sampling;

    public:
        SelfGrammarIndexPTS(const int &);
        virtual ~SelfGrammarIndexPTS();

        void build(const std::string& ) override ;

        void build(const SelfGrammarIndex::grammar_representation & G,
                   const SelfGrammarIndex::range_search2d & R,
                   const m_patricia::compact_patricia_tree &sfx,
                   const m_patricia::compact_patricia_tree &rules,
                   const unsigned int &);

        void set_code(const unsigned int & c){ SelfGrammarIndexPT::set_code(c);}
        size_t size_in_bytes() const override ;


        const m_patricia::compact_patricia_tree& get_pt_rules()const{ return SelfGrammarIndexPT::get_pt_rules();}
        const m_patricia::compact_patricia_tree& get_pt_suffixes()const{ return SelfGrammarIndexPT::get_pt_suffixes();}

        void locate2( std::string& , sdsl::bit_vector &)  ;
        void locate2( std::string & , std::vector<uint> & );
        void locate( std::string & , std::vector<uint> & );
        void locateNoTrie( std::string &, std::vector<uint> &);
        compressed_grammar& get_grammar(){ return _g;}
        void display(const std::size_t& , const std::size_t&, std::string & ) override ;

        void save(std::fstream& ) override;

        void load(std::fstream& ) override;

        void load_basics(std::fstream& f){
            SelfGrammarIndex::load_basics(f);
        }
        void build_suffix(const string & ,fstream & ,fstream & );




        void test_findSecondOcc(long len,binary_relation::bin_long x1,binary_relation::bin_long x2,binary_relation::bin_long y1,binary_relation::bin_long y2,std::vector<uint> &occ){

            const auto& g_tree = _g.get_parser_tree();
            std::vector< std::pair<size_t,size_t> > pairs;
            grid.range2(x1,x2,y1,y2,pairs);



            //long len = itera-pattern.begin() +1;
            for (auto &pair : pairs) {
                size_t p = grid.first_label_col(pair.second);
                size_t pos_p = _g.offsetText(g_tree[p]);
                unsigned int parent = g_tree.parent(g_tree[p]);
                long int  l = (- len + pos_p) - _g.offsetText(parent);
                find_second_occ(l,parent,occ);
            }

        }

    void find_ranges_trie(std::string &, std::vector<uint>& );
    void find_ranges_trie(std::string &, std::vector<uint>& , std::vector<range> &);
    void find_ranges(std::string &, std::vector<uint> &);
    void find_ranges_dfs(std::string &, std::vector<uint>& ){}

    void load_rules_pt(fstream& f){ SelfGrammarIndexPT::load_rules_pt(f);}
    void load_sfx_pt(fstream& f){ SelfGrammarIndexPT::load_sfx_pt(f);}

    protected:

        void sampling_range_suff(size_t& i, size_t& j, std::string::iterator& , std::string::iterator& )const;

        void sampling_range_rules(size_t &i, size_t &j, std::string::iterator& , std::string::iterator& )const;


        size_t _st(const size_t & i)const;





};


#endif //IMPROVED_GRAMMAR_INDEX_SELFGRAMMARINDEXPTS_H
