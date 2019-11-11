#ifndef SCATTER_H_
#define SCATTER_H_

// Simple wrapper to perserve original hierarchy.
template <typename ...Ts>
struct TypeList;

// Drops GenScatterHierarchy<Unit, EmptyType> as last element
// in chain to simplify implementation using parameter packs
// while preserving the ability to reduce to one-element version
// of hierarchy.
template <template <typename> typename Unit, typename T>
class GenScatterHierarchy;

template <template <typename> typename Unit, typename AtomicType>
class GenScatterHierarchy : public Unit<AtomicType> {
 public:
  using LeftBase = Unit<AtomicType>;
};

// Required to avoid inaccessible ambiguous base problem.
template <typename Head, typename ...Tail>
class LeftBaseTag;

template <template <typename> typename Unit, typename Head, typename ...Tail>
class GenScatterHierarchy<Unit, LeftBaseTag<Head, Tail...>>
  : public GenScatterHierarchy<Unit, Head> {};

template <template <typename> typename Unit, typename Head, typename ...Tail>
class GenScatterHierarchy<Unit, TypeList<Head, Tail...>>
  : public GenScatterHierarchy<Unit, LeftBaseTag<Head, Tail...>>,
    public GenScatterHierarchy<Unit, TypeList<Tail...>> {
 public:
  using LeftBase = GenScatterHierarchy<Unit, LeftBaseTag<Head, Tail...>>;
  using RightBase = GenScatterHierarchy<Unit, TypeList<Tail...>>;
};

template <template <typename> typename Unit>
class GenScatterHierarchy<Unit, TypeList<>> {};

// Does not work for types with duplicates. Use FieldAt instead.
template <
  typename AtomicType,
  template <typename> typename Unit,
  typename ...Ts
>
Unit<AtomicType> & Field(GenScatterHierarchy<Unit, TypeList<Ts...>> &hierarchy) {
  return hierarchy; // triggers auto-conversion.
}

template <
  int position,
  template <typename> typename Unit,
  typename ...Ts
>
class FieldAtHelper;

template <
  template <typename> typename Unit,
  typename Head,
  typename ...Tail
>
class FieldAtHelper<0, Unit, Head, Tail...> {
 public:
  using AtomicType = Head;

  static Unit<AtomicType> & Field(GenScatterHierarchy<Unit, TypeList<Head, Tail...>> &h) {
    typename GenScatterHierarchy<Unit, TypeList<Head, Tail...>>::LeftBase &left = h;
    return left;
  }
};

template <
  int position,
  template <typename> typename Unit,
  typename Head,
  typename ...Tail
>
class FieldAtHelper<position, Unit, Head, Tail...> {
 public:
  using AtomicType = typename FieldAtHelper<position - 1, Unit, Tail...>::AtomicType;

  static Unit<AtomicType> & Field(GenScatterHierarchy<Unit, TypeList<Head, Tail...>> &h) {
    return FieldAtHelper<position - 1, Unit, Tail...>::Field(h);
  }
};

template <
  int position,
  template <typename> typename Unit,
  typename ...Ts
>
Unit<
  typename FieldAtHelper<position, Unit, Ts...>::AtomicType
> & FieldAt(GenScatterHierarchy<Unit, TypeList<Ts...>> &hierarchy) {
  return FieldAtHelper<position, Unit, Ts...>::Field(hierarchy);
}

#endif // SCATTER_H_
