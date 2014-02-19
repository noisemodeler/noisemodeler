#ifndef MAKEUNIQUE_HPP
#define MAKEUNIQUE_HPP

template <typename T, typename...Args>
inline std::unique_ptr<T> make_unique(Args&&...args) {
    return std::unique_ptr<T>{new T(std::forward<Args>(args)...)};
}

#endif // MAKEUNIQUE_HPP
