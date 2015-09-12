#define CPPJIEAB_JIEBA_H

#include "QuerySegment.hpp"
#include "PosTagger.hpp"
#include "LevelSegment.hpp"

namespace CppJieba {

class Jieba {
 public:
  Jieba(const string& dict_path, const string& model_path, const string& user_dict_path) 
    : dict_trie_(dict_path, user_dict_path),
      model_(model_path),
      mp_seg_(&dict_trie_),
      hmm_seg_(&model_),
      mix_seg_(&dict_trie_, &model_),
      full_seg_(&dict_trie_),
      query_seg_(&dict_trie_, &model_),
      level_seg_(&dict_trie_) {
  }
  ~Jieba() {
  }

  void Cut(const string& sentence, bool hmm, vector<string>& words) const {
    if (hmm) {
      mix_seg_.cut(sentence, words);
    } else {
      mp_seg_.cut(sentence, words);
    }
  }
  void CutAll(const string& sentence, vector<string>& words) const {
    full_seg_.cut(sentence, words);
  }
  void CutForSearch(const string& sentence, vector<string>& words) const {
    query_seg_.cut(sentence, words);
  }
  void CutHMM(const string& sentence, vector<string>& words) const {
    hmm_seg_.cut(sentence, words);
  }
  void CutLevel(const string& sentence, vector<string>& words) const {
    level_seg_.cut(sentence, words);
  }
  void CutLevel(const string& sentence, vector<pair<string, size_t> >& words) const {
    level_seg_.cut(sentence, words);
  }
  void CutSmall(const string& sentence, vector<string>& words, size_t max_word_len) const {
    mp_seg_.cut(sentence, words, max_word_len);
  }
  bool InsertUserWord(const string& word, const string& tag = UNKNOWN_TAG) {
    return dict_trie_.insertUserWord(word, tag);
  }

  const DictTrie* GetDictTrie() const {
    return &dict_trie_;
  } 
  const HMMModel* GetHMMModel() const {
    return &model_;
  }

 private:
  DictTrie dict_trie_;
  HMMModel model_;
  
  // They share the same dict trie and model
  MPSegment mp_seg_;
  HMMSegment hmm_seg_;
  MixSegment mix_seg_;
  FullSegment full_seg_;
  QuerySegment query_seg_;
  LevelSegment level_seg_;
  
}; // class 

} // namespace 
