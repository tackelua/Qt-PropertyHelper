#pragma once
#include <QObject>
// See Gist Comment for description, usage, warnings and license information
#define AUTO_PROPERTY(TYPE, NAME)                                 \
  Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME##Changed) \
 public:                                                          \
  TYPE NAME() const { return a_##NAME; }                          \
  void NAME(const TYPE& value) {                                  \
    if (a_##NAME == value) return;                                \
    a_##NAME = value;                                             \
    emit NAME##Changed(value);                                    \
  }                                                               \
  Q_SIGNAL void NAME##Changed(TYPE value);                        \
                                                                  \
 private:                                                         \
  TYPE a_##NAME;

#define READONLY_PROPERTY(TYPE, NAME)      \
  Q_PROPERTY(TYPE NAME READ NAME CONSTANT) \
 public:                                   \
  TYPE NAME() const { return a_##NAME; }   \
                                           \
 private:                                  \
  TYPE a_##NAME;

#define READ_PROPERTY(TYPE, NAME)                      \
  Q_PROPERTY(TYPE NAME READ NAME NOTIFY NAME##Changed) \
 public:                                               \
  TYPE NAME() const { return a_##NAME; }               \
  Q_SIGNAL void NAME##Changed(TYPE value);             \
                                                       \
 private:                                              \
  TYPE a_##NAME;
