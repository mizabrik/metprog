struct EmptyList {};

template <typename H, typename T>
struct TypeList {
  typedef H Head;
  typedef T Tail;
};

template <typename T, typename TL>
struct IndexOf;

template <typename T>
struct IndexOf<T, EmptyList> {
  static const int index = -1;
};

template <typename T, typename Tail>
struct IndexOf<T, TypeList<T, Tail> > {
  static const int index = 0;
};

template <typename T, typename Head, typename Tail>
struct IndexOf<T, TypeList<Head, Tail> > {
  static const int index = IndexOf<T, Tail>::index == -1
      ? -1
      : IndexOf<T, Tail>::index + 1;
};

template <typename T, typename TL>
int GetIndexOf() {
  return IndexOf<T, TL>::index;
}

template <int H, typename T>
struct IntList {
  enum {Head = H};
  typedef T Tail;
};

template <typename T, typename TL, int i = 0>
struct IndicesOf;

template <typename T, int i>
struct IndicesOf<T, EmptyList, i> {
  typedef EmptyList indices;
};

template <typename T, typename Tail, int i>
struct IndicesOf<T, TypeList<T, Tail>, i> {
  typedef IntList<
      i,
      typename IndicesOf<T, Tail, i + 1>::indices
  > indices;
};

template <typename T, typename Head, typename Tail, int i>
struct IndicesOf<T, TypeList<Head, Tail>, i> {
  typedef typename IndicesOf<T, Tail, i + 1>::indices indices;
};
