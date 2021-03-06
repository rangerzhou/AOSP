//===-  X86Relocator.h --------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#ifndef TARGET_X86_X86RELOCATOR_H_
#define TARGET_X86_X86RELOCATOR_H_

#include "mcld/LD/Relocator.h"
#include "mcld/Target/GOT.h"
#include "mcld/Target/PLT.h"
#include "mcld/Target/KeyEntryMap.h"
#include "X86LDBackend.h"

namespace mcld {

class LinkerConfig;
class ResolveInfo;

/** \class X86Relocator
 *  \brief X86Relocator creates and destroys the X86 relocations.
 *
 */
class X86Relocator : public Relocator {
 public:
  typedef KeyEntryMap<ResolveInfo, PLTEntryBase> SymPLTMap;

  /** \enum ReservedEntryType
   *  \brief The reserved entry type of reserved space in ResolveInfo.
   *
   *  This is used for sacnRelocation to record what kinds of entries are
   *  reserved for this resolved symbol. In X86, there are three kinds of
   *  entries, GOT, PLT, and dynamic reloction.
   *
   *  bit:  3     2     1     0
   *   |    | PLT | GOT | Rel |
   *
   *  value    Name         - Description
   *
   *  0000     None         - no reserved entry
   *  0001     ReserveRel   - reserve an dynamic relocation entry
   *  0010     ReserveGOT   - reserve an GOT entry
   *  0100     ReservePLT   - reserve an PLT entry and the corresponding GOT,
   *
   */
  enum ReservedEntryType {
    None = 0,
    ReserveRel = 1,
    ReserveGOT = 2,
    ReservePLT = 4,
  };

  /** \enum EntryValue
   *  \brief The value of the entries. The symbol value will be decided at after
   *  layout, so we mark the entry during scanRelocation and fill up the actual
   *  value when applying relocations.
   */
  enum EntryValue { Default = 0, SymVal = 1 };

 public:
  explicit X86Relocator(const LinkerConfig& pConfig);
  ~X86Relocator();

  virtual Result applyRelocation(Relocation& pRelocation) = 0;

  virtual const char* getName(Relocation::Type pType) const = 0;

  const SymPLTMap& getSymPLTMap() const { return m_SymPLTMap; }
  SymPLTMap& getSymPLTMap() { return m_SymPLTMap; }

  /// scanRelocation - determine the empty entries are needed or not and create
  /// the empty entries if needed.
  /// For X86, following entries are check to create:
  /// - GOT entry (for .got and .got.plt sections)
  /// - PLT entry (for .plt section)
  /// - dynamin relocation entries (for .rel.plt and .rel.dyn sections)
  void scanRelocation(Relocation& pReloc,
                      IRBuilder& pBuilder,
                      Module& pModule,
                      LDSection& pSection,
                      Input& pInput);

 protected:
  /// addCopyReloc - add a copy relocation into .rel.dyn for pSym
  /// @param pSym - A resolved copy symbol that defined in BSS section
  void addCopyReloc(ResolveInfo& pSym, X86GNULDBackend& pTarget);

  /// defineSymbolforCopyReloc - allocate a space in BSS section and
  /// and force define the copy of pSym to BSS section
  /// @return the output LDSymbol of the copy symbol
  LDSymbol& defineSymbolforCopyReloc(IRBuilder& pLinker,
                                     const ResolveInfo& pSym,
                                     X86GNULDBackend& pTarget);

 private:
  virtual void scanLocalReloc(Relocation& pReloc,
                              IRBuilder& pBuilder,
                              Module& pModule,
                              LDSection& pSection) = 0;

  virtual void scanGlobalReloc(Relocation& pReloc,
                               IRBuilder& pBuilder,
                               Module& pModule,
                               LDSection& pSection) = 0;

 private:
  SymPLTMap m_SymPLTMap;
};

/** \class X86_32Relocator
 *  \brief X86_32Relocator creates and destroys the X86-32 relocations.
 *
 */
class X86_32Relocator : public X86Relocator {
 public:
  typedef KeyEntryMap<ResolveInfo, X86_32GOTEntry> SymGOTMap;
  typedef KeyEntryMap<ResolveInfo, X86_32GOTEntry> SymGOTPLTMap;

  enum {
    R_386_TLS_OPT = 44  // mcld internal relocation type
  };

 public:
  X86_32Relocator(X86_32GNULDBackend& pParent, const LinkerConfig& pConfig);

  Result applyRelocation(Relocation& pRelocation);

  X86_32GNULDBackend& getTarget() { return m_Target; }

  const X86_32GNULDBackend& getTarget() const { return m_Target; }

  const char* getName(Relocation::Type pType) const;

  Size getSize(Relocation::Type pType) const;

  const SymGOTMap& getSymGOTMap() const { return m_SymGOTMap; }
  SymGOTMap& getSymGOTMap() { return m_SymGOTMap; }

  const SymGOTPLTMap& getSymGOTPLTMap() const { return m_SymGOTPLTMap; }
  SymGOTPLTMap& getSymGOTPLTMap() { return m_SymGOTPLTMap; }

  X86_32GOTEntry& getTLSModuleID();

  /// mayHaveFunctionPointerAccess - check if the given reloc would possibly
  /// access a function pointer.
  virtual bool mayHaveFunctionPointerAccess(const Relocation& pReloc) const;

  /// getDebugStringOffset - get the offset from the relocation target. This is
  /// used to get the debug string offset.
  uint32_t getDebugStringOffset(Relocation& pReloc) const;

  /// applyDebugStringOffset - apply the relocation target to specific offset.
  /// This is used to set the debug string offset.
  void applyDebugStringOffset(Relocation& pReloc, uint32_t pOffset);

 private:
  void scanLocalReloc(Relocation& pReloc,
                      IRBuilder& pBuilder,
                      Module& pModule,
                      LDSection& pSection);

  void scanGlobalReloc(Relocation& pReloc,
                       IRBuilder& pBuilder,
                       Module& pModule,
                       LDSection& pSection);

  /// -----  tls optimization  ----- ///
  /// convert R_386_TLS_IE to R_386_TLS_LE
  void convertTLSIEtoLE(Relocation& pReloc, LDSection& pSection);

 private:
  X86_32GNULDBackend& m_Target;
  SymGOTMap m_SymGOTMap;
  SymGOTPLTMap m_SymGOTPLTMap;
};

/** \class X86_64Relocator
 *  \brief X86_64Relocator creates and destroys the X86-64 relocations.
 *
 */
class X86_64Relocator : public X86Relocator {
 public:
  typedef KeyEntryMap<ResolveInfo, X86_64GOTEntry> SymGOTMap;
  typedef KeyEntryMap<ResolveInfo, X86_64GOTEntry> SymGOTPLTMap;
  typedef KeyEntryMap<Relocation, Relocation> RelRelMap;

 public:
  X86_64Relocator(X86_64GNULDBackend& pParent, const LinkerConfig& pConfig);

  Result applyRelocation(Relocation& pRelocation);

  X86_64GNULDBackend& getTarget() { return m_Target; }

  const X86_64GNULDBackend& getTarget() const { return m_Target; }

  const char* getName(Relocation::Type pType) const;

  Size getSize(Relocation::Type pType) const;

  const SymGOTMap& getSymGOTMap() const { return m_SymGOTMap; }
  SymGOTMap& getSymGOTMap() { return m_SymGOTMap; }

  const SymGOTPLTMap& getSymGOTPLTMap() const { return m_SymGOTPLTMap; }
  SymGOTPLTMap& getSymGOTPLTMap() { return m_SymGOTPLTMap; }

  const RelRelMap& getRelRelMap() const { return m_RelRelMap; }
  RelRelMap& getRelRelMap() { return m_RelRelMap; }

  /// mayHaveFunctionPointerAccess - check if the given reloc would possibly
  /// access a function pointer.
  virtual bool mayHaveFunctionPointerAccess(const Relocation& pReloc) const;

  /// getDebugStringOffset - get the offset from the relocation target. This is
  /// used to get the debug string offset.
  uint32_t getDebugStringOffset(Relocation& pReloc) const;

  /// applyDebugStringOffset - apply the relocation target to specific offset.
  /// This is used to set the debug string offset.
  void applyDebugStringOffset(Relocation& pReloc, uint32_t pOffset);

 private:
  void scanLocalReloc(Relocation& pReloc,
                      IRBuilder& pBuilder,
                      Module& pModule,
                      LDSection& pSection);

  void scanGlobalReloc(Relocation& pReloc,
                       IRBuilder& pBuilder,
                       Module& pModule,
                       LDSection& pSection);

 private:
  X86_64GNULDBackend& m_Target;
  SymGOTMap m_SymGOTMap;
  SymGOTPLTMap m_SymGOTPLTMap;
  RelRelMap m_RelRelMap;
};

}  // namespace mcld

#endif  // TARGET_X86_X86RELOCATOR_H_
