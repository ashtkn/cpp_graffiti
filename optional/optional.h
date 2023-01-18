#pragma once

#include <stdexcept>

namespace mylib {

class bad_optional_access : public std::exception {
  public:
    const char* what() const noexcept override {
      return "bad_optional_access";
    }
};

template <typename T>
class optional {
 public:
  /**
   * @brief コンストラクタ．無効値を生成する．
   */
  constexpr optional() noexcept : value_(), has_value_(false) {}

  /**
   * @brief コンストラクタ．有効値を生成する．
   */
  constexpr explicit optional(const T& v) : value_(v), has_value_(true) {}

  /**
   * @brief コピーコンストラクタ
   */
  constexpr optional(const optional& rhs)
      : value_(rhs.value_), has_value_(rhs.has_value_) {}

  /**
   * @brief ムーブコンストラクタ
   */
  constexpr optional(optional&& rhs) noexcept
      : value_(std::move(rhs.value_)), has_value_(rhs.has_value_) {}

  /**
   * @brief デストラクタ
   */
  ~optional() = default;

  /**
   * @brief コピー代入演算子
   */
  optional& operator=(const optional& rhs) {
    if (this != &rhs) {
      value_ = rhs.value_;
      has_value_ = rhs.has_value_;
    }
    return *this;
  }

  /**
   * @brief ムーブ代入演算子
   */
  optional& operator=(optional&& rhs) noexcept {
    if (this != &rhs) {
      value_ = std::move(rhs.value_);
      has_value_ = rhs.has_value_;
    }
    return *this;
  }

  /**
   * @brief 有効値かどうかを返す．
   */
  constexpr explicit operator bool() const noexcept { return has_value_; }

  /**
   * @brief 有効値かどうかを返す．
   */
  constexpr bool has_value() const noexcept { return has_value_; }

  /**
   * @brief メンバアクセス演算子
   */
  constexpr T* operator->() noexcept { return &value_; }

  /**
   * @brief メンバアクセス演算子
   */
  constexpr const T* operator->() const noexcept { return &value_; }

  /**
   * @brief 間接参照演算子（左辺値参照）
   */
  constexpr T& operator*() & noexcept { return value_; }

  /**
   * @brief 間接参照演算子（右辺値参照）
   */
  constexpr T&& operator*() && noexcept { return std::move(value_); };

  /**
   * @brief 間接参照演算子（const左辺値参照）
   */
  constexpr const T& operator*() const& noexcept { return value_; }

  /**
   * @brief 間接参照演算子（const右辺値参照）
   */
  constexpr const T&& operator*() const&& noexcept { return std::move(value_); }

  /**
   * @brief 保持値への左辺値参照を取得する．
   */
  constexpr T& value() & {
    if (!has_value_) {
      throw bad_optional_access();
    }
    return value_;
  }

  /**
   * @brief 保持値への右辺値参照を取得する．
   */
  constexpr T&& value() && {
    if (!has_value_) {
      throw bad_optional_access();
    }
    return std::move(value_);
  }

  /**
   * @brief 保持値へのconst左辺値参照を取得する．
   */
  constexpr const T& value() const& {
    if (!has_value_) {
      throw bad_optional_access();
    }
    return value_;
  }

  /**
   * @brief 保持値へのconst右辺値参照を取得する．
   */
  constexpr const T&& value() const&& {
    if (!has_value_) {
      throw bad_optional_access();
    }
    return std::move(value_);
  }

 private:
  T value_;
  bool has_value_;
};

} // namespace mylib
