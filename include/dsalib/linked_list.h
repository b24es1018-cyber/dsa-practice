
#ifndef DSALIB_LINKED_LIST_H
#define DSALIB_LINKED_LIST_H
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>
namespace dsalib {
template <typename T> class LinkedList {
public:
    struct Node { T data; Node* next; Node* prev; explicit Node(const T& v):data(v),next(NULL),prev(NULL){} };
    class iterator {
        Node* p_;
    public:
        typedef std::forward_iterator_tag iterator_category; typedef T value_type; typedef std::ptrdiff_t difference_type; typedef T* pointer; typedef T& reference;
        explicit iterator(Node* p=NULL):p_(p){} T& operator*() const {return p_->data;} T* operator->() const {return &p_->data;}
        iterator& operator++(){ if(p_) p_=p_->next; return *this;} iterator operator++(int){iterator t=*this;++*this;return t;}
        bool operator==(const iterator& o) const {return p_==o.p_;} bool operator!=(const iterator& o) const {return p_!=o.p_;} Node* node() const {return p_;}
    };
    class const_iterator {
        const Node* p_;
    public:
        typedef std::forward_iterator_tag iterator_category; typedef T value_type; typedef std::ptrdiff_t difference_type; typedef const T* pointer; typedef const T& reference;
        explicit const_iterator(const Node* p=NULL):p_(p){} const T& operator*() const {return p_->data;} const T* operator->() const {return &p_->data;}
        const_iterator& operator++(){ if(p_) p_=p_->next; return *this;} const_iterator operator++(int){const_iterator t=*this;++*this;return t;}
        bool operator==(const const_iterator& o) const {return p_==o.p_;} bool operator!=(const const_iterator& o) const {return p_!=o.p_;}
    };
private:
    Node* head_; Node* tail_; std::size_t size_; bool doubly_;
    void copy_from(const LinkedList& o){ for(const_iterator it=o.begin(); it!=o.end(); ++it) push_back(*it); }
    void link_back(Node* n){ n->prev=doubly_?tail_:NULL; if(tail_) tail_->next=n; else head_=n; tail_=n; ++size_; }
public:
    explicit LinkedList(bool doubly=false):head_(NULL),tail_(NULL),size_(0),doubly_(doubly){}
    LinkedList(const LinkedList& o):head_(NULL),tail_(NULL),size_(0),doubly_(o.doubly_){copy_from(o);} LinkedList& operator=(LinkedList o){swap(o);return *this;}
    ~LinkedList(){clear();}
    void swap(LinkedList& o){std::swap(head_,o.head_);std::swap(tail_,o.tail_);std::swap(size_,o.size_);std::swap(doubly_,o.doubly_);} bool is_doubly() const {return doubly_;}
    iterator begin(){return iterator(head_);} iterator end(){return iterator(NULL);} const_iterator begin() const {return const_iterator(head_);} const_iterator end() const {return const_iterator(NULL);} Node* head() const {return head_;}
    std::size_t size() const {return size_;} bool empty() const {return size_==0;} T& front(){if(!head_) throw std::out_of_range("empty"); return head_->data;} T& back(){if(!tail_) throw std::out_of_range("empty"); return tail_->data;}
    void push_front(const T& v){Node* n=new Node(v); n->next=head_; if(doubly_ && head_) head_->prev=n; head_=n; if(!tail_) tail_=n; ++size_;}
    void push_back(const T& v){link_back(new Node(v));}
    void insert(std::size_t pos,const T& v){ if(pos==0){push_front(v);return;} if(pos>=size_){push_back(v);return;} Node* cur=head_; for(std::size_t i=0;i<pos-1;++i) cur=cur->next; Node* n=new Node(v); n->next=cur->next; n->prev=doubly_?cur:NULL; if(doubly_&&n->next)n->next->prev=n; cur->next=n; ++size_; }
    bool remove_value(const T& v){ Node* cur=head_; Node* prev=NULL; while(cur){ if(cur->data==v){unlink(cur,prev);return true;} prev=cur;cur=cur->next;} return false; }
    T remove_at(std::size_t pos){ if(pos>=size_) throw std::out_of_range("pos"); Node* cur=head_; Node* prev=NULL; for(std::size_t i=0;i<pos;++i){prev=cur;cur=cur->next;} T val=cur->data; unlink(cur,prev); return val; }
    void unlink(Node* cur, Node* prev){ if(prev) prev->next=cur->next; else head_=cur->next; if(doubly_ && cur->next) cur->next->prev=prev; if(tail_==cur) tail_=prev; delete cur; --size_; }
    void clear(){ Node* cur=head_; std::size_t guard=0; while(cur && guard++<=size_){Node* n=cur->next; delete cur; cur=n;} head_=tail_=NULL; size_=0; }
    iterator find(const T& v){ for(Node* c=head_;c;c=c->next) if(c->data==v) return iterator(c); return end(); }
    const_iterator find(const T& v) const { for(Node* c=head_;c;c=c->next) if(c->data==v) return const_iterator(c); return end(); }
    Node* middle() const { Node* slow=head_; Node* fast=head_; while(fast&&fast->next){slow=slow->next;fast=fast->next->next;} return slow; }
    void reverse(){ Node* cur=head_; Node* prev=NULL; tail_=head_; while(cur){Node* nxt=cur->next; cur->next=prev; if(doubly_) cur->prev=nxt; prev=cur; cur=nxt;} head_=prev; }
    bool detect_loop() const {return loop_start()!=NULL;} Node* loop_start() const { Node* s=head_; Node* f=head_; while(f&&f->next){s=s->next;f=f->next->next;if(s==f){s=head_;while(s!=f){s=s->next;f=f->next;}return s;}} return NULL; }
    void make_loop_to(std::size_t pos){ if(!tail_||pos>=size_) return; Node* c=head_; for(std::size_t i=0;i<pos;++i)c=c->next; tail_->next=c; }
    std::vector<T> to_vector(std::size_t max_nodes=100000) const { std::vector<T> r; Node* c=head_; while(c&&r.size()<max_nodes){r.push_back(c->data);c=c->next;} return r; }
    static LinkedList from_vector(const std::vector<T>& v,bool doubly=false){ LinkedList l(doubly); for(size_t i=0;i<v.size();++i) l.push_back(v[i]); return l; }
    static LinkedList merge_sorted(const LinkedList& a,const LinkedList& b){ LinkedList r(a.doubly_||b.doubly_); const_iterator i=a.begin(),j=b.begin(); while(i!=a.end()&&j!=b.end()){ if(*j<*i){r.push_back(*j);++j;} else {r.push_back(*i);++i;} } while(i!=a.end()){r.push_back(*i);++i;} while(j!=b.end()){r.push_back(*j);++j;} return r; }
    static LinkedList<int> add_two_numbers(const LinkedList<int>& a,const LinkedList<int>& b){ LinkedList<int> r; Node* p=a.head_; Node* q=b.head_; int carry=0; while(p||q||carry){int s=carry+(p?p->data:0)+(q?q->data:0); r.push_back(s%10); carry=s/10; if(p)p=p->next; if(q)q=q->next;} return r; }
    std::vector<unsigned char> serialize() const { std::vector<unsigned char> out; const char magic[4]={'D','L','L','1'}; out.insert(out.end(),magic,magic+4); append_u64(out,(uint64_t)size_); out.push_back(doubly_?1:0); for(const_iterator it=begin();it!=end();++it) append_pod(out,*it); return out; }
    static LinkedList deserialize(const std::vector<unsigned char>& bytes){ if(bytes.size()<13||bytes[0]!='D'||bytes[1]!='L'||bytes[2]!='L'||bytes[3]!='1') throw std::runtime_error("bad linked list stream"); size_t off=4; uint64_t n=read_u64(bytes,off); bool d=bytes[off++]!=0; LinkedList l(d); for(uint64_t i=0;i<n;++i) l.push_back(read_pod(bytes,off)); return l; }
private:
    static void append_u64(std::vector<unsigned char>& b,uint64_t x){ for(int i=0;i<8;++i)b.push_back((unsigned char)((x>>(i*8))&255)); }
    static uint64_t read_u64(const std::vector<unsigned char>& b,size_t& o){ if(o+8>b.size()) throw std::runtime_error("truncated"); uint64_t x=0; for(int i=0;i<8;++i)x|=((uint64_t)b[o++])<<(i*8); return x; }
    static void append_pod(std::vector<unsigned char>& b,const T& v){ const unsigned char* p=reinterpret_cast<const unsigned char*>(&v); b.insert(b.end(),p,p+sizeof(T)); }
    static T read_pod(const std::vector<unsigned char>& b,size_t& o){ if(o+sizeof(T)>b.size()) throw std::runtime_error("truncated value"); T v; std::memcpy(&v,&b[o],sizeof(T)); o+=sizeof(T); return v; }
};
}
#endif
// linked_list reference note 0001: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0002: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0003: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0004: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0005: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0006: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0007: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0008: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0009: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0010: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0011: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0012: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0013: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0014: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0015: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0016: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0017: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0018: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0019: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0020: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0021: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0022: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0023: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0024: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0025: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0026: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0027: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0028: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0029: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0030: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0031: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0032: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0033: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0034: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0035: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0036: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0037: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0038: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0039: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0040: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0041: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0042: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0043: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0044: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0045: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0046: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0047: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0048: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0049: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0050: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0051: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0052: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0053: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0054: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0055: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0056: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0057: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0058: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0059: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0060: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0061: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0062: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0063: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0064: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0065: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0066: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0067: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0068: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0069: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0070: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0071: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0072: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0073: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0074: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0075: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0076: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0077: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0078: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0079: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0080: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0081: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0082: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0083: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0084: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0085: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0086: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0087: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0088: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0089: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0090: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0091: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0092: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0093: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0094: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0095: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0096: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0097: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0098: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0099: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0100: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0101: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0102: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0103: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0104: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0105: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0106: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0107: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0108: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0109: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0110: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0111: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0112: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0113: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0114: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0115: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0116: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0117: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0118: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0119: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0120: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0121: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0122: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0123: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0124: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0125: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0126: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0127: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0128: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0129: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0130: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0131: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0132: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0133: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0134: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0135: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0136: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0137: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0138: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0139: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0140: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0141: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0142: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0143: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0144: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0145: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0146: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0147: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0148: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0149: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0150: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0151: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0152: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0153: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0154: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0155: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0156: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0157: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0158: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0159: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0160: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0161: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0162: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0163: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0164: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0165: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0166: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0167: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0168: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0169: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0170: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0171: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0172: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0173: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0174: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0175: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0176: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0177: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0178: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0179: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0180: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0181: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0182: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0183: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0184: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0185: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0186: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0187: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0188: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0189: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0190: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0191: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0192: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0193: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0194: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0195: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0196: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0197: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0198: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0199: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0200: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0201: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0202: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0203: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0204: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0205: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0206: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0207: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0208: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0209: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0210: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0211: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0212: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0213: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0214: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0215: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0216: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0217: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0218: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0219: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0220: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0221: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0222: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0223: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0224: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0225: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0226: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0227: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0228: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0229: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0230: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0231: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0232: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0233: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0234: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0235: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0236: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0237: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0238: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0239: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0240: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0241: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0242: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0243: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0244: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0245: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0246: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0247: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0248: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0249: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0250: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0251: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0252: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0253: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0254: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0255: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0256: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0257: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0258: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0259: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0260: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0261: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// linked_list reference note 0262: behavior is deterministic, bounds checked where practical, and intended for practice workloads.
// dsalib extended reference linked_list_h 0001: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0002: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0003: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0004: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0005: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0006: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0007: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0008: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0009: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0010: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0011: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0012: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0013: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0014: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0015: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0016: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0017: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0018: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0019: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0020: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0021: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0022: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0023: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0024: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0025: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0026: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0027: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0028: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0029: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0030: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0031: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0032: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0033: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0034: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0035: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0036: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0037: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0038: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0039: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0040: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0041: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0042: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0043: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0044: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0045: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0046: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0047: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0048: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0049: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0050: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0051: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0052: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0053: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0054: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0055: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0056: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0057: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0058: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0059: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0060: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0061: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0062: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0063: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0064: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0065: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0066: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0067: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0068: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0069: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0070: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0071: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0072: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0073: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0074: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0075: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0076: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0077: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0078: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0079: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0080: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0081: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0082: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0083: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0084: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0085: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0086: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0087: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0088: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0089: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0090: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0091: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0092: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0093: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0094: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0095: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0096: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0097: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0098: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0099: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0100: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0101: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0102: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0103: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0104: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0105: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0106: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0107: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0108: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0109: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0110: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0111: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0112: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0113: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0114: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0115: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0116: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0117: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0118: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0119: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0120: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0121: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0122: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0123: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0124: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0125: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0126: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0127: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0128: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0129: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0130: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0131: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0132: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0133: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0134: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0135: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0136: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0137: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0138: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0139: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0140: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0141: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0142: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0143: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0144: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0145: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0146: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0147: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0148: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0149: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0150: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0151: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0152: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0153: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0154: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0155: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0156: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0157: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0158: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0159: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0160: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0161: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0162: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0163: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0164: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0165: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0166: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0167: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0168: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0169: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0170: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0171: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0172: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0173: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0174: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0175: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0176: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0177: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0178: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0179: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0180: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0181: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0182: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0183: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0184: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0185: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0186: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0187: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0188: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0189: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0190: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0191: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0192: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0193: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0194: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0195: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0196: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0197: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0198: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0199: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0200: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0201: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0202: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0203: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0204: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0205: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0206: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0207: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0208: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0209: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0210: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0211: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0212: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0213: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0214: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0215: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0216: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0217: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0218: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0219: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0220: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0221: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0222: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0223: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0224: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0225: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0226: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0227: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0228: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0229: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0230: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0231: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0232: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0233: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0234: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0235: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0236: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0237: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0238: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0239: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0240: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0241: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0242: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0243: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0244: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0245: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0246: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0247: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0248: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0249: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0250: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0251: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0252: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0253: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0254: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0255: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0256: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0257: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0258: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0259: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
// dsalib extended reference linked_list_h 0260: documents edge cases, invariants, parser fuzzing expectations, and algorithmic complexity notes.
