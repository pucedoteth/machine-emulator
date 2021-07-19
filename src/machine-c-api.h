// Copyright 2021 Cartesi Pte. Ltd.
//
// This file is part of the machine-emulator. The machine-emulator is free
// software: you can redistribute it and/or modify it under the terms of the GNU
// Lesser General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// The machine-emulator is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the machine-emulator. If not, see http://www.gnu.org/licenses/.
//

/// \file
/// \brief Cartesi machine emulator C API interface

#ifndef CM_C_API_H
#define CM_C_API_H


#ifndef __cplusplus
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#else
#include <cassert>
#include <cstddef>
#include <cstdint>
#endif

#include "machine-c-defines.h"

#ifdef __cplusplus
extern "C" {
#endif


// ---------------------------------
// API Structures
// ---------------------------------

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays,modernize-use-using)
typedef uint8_t cm_hash[CM_MACHINE_HASH_BYTE_SIZE];

///brief Error codes returned from machine emulator C API
enum CM_ERROR {
    CM_ERROR_OK = 0,
    //Logic errors
    CM_ERROR_INVALID_ARGUMENT,
    CM_ERROR_DOMAIN_ERROR,
    CM_ERROR_LENGTH_ERROR,
    CM_ERROR_OUT_OF_RANGE,
    CM_ERROR_FUTURE_ERROR,
    CM_ERROR_LOGIC_ERROR,
    CM_LOGIC_ERROR_END,
    // Bad optional access error
    CM_ERROR_BAD_OPTIONAL_ACCESS,
    // Runtime errors
    CM_ERROR_RUNTIME_ERROR,
    CM_ERROR_RANGE_ERROR,
    CM_ERROR_OVERFLOW_ERROR,
    CM_ERROR_UNDERFLOW_ERROR,
    CM_ERROR_REGEX_ERROR,
    CM_ERROR_SYSTEM_IOS_BASE_FAILURE,
    CM_ERROR_FILESYSTEM_ERROR,
    CM_ERROR_ATOMIC_TX_ERROR,
    CM_ERROR_NONEXISTING_LOCAL_TIME,
    CM_ERROR_AMBIGOUS_LOCAL_TIME,
    CM_ERROR_FORMAT_ERROR,
    CM_RUNTIME_ERROR_END,
    //Other errors
    CM_ERROR_BAD_TYPEID,
    CM_ERROR_BAD_CAST,
    CM_ERROR_BAD_ANY_CAST,
    CM_ERROR_BAD_WEAK_PTR,
    CM_ERROR_BAD_FUNCTION_CALL,
    CM_ERROR_BAD_ALLOC,
    CM_ERROR_BAD_ARRAY_NEW_LENGTH,
    CM_ERROR_BAD_EXCEPTION,
    CM_ERROR_BAD_VARIANT_ACCESS,
    CM_ERROR_EXCEPTION,
    CM_OTHER_ERROR_END,
    //C API Errors
    CM_ERROR_UNKNOWN
};

/// \brief List of CSRs to use with read_csr and write_csr
typedef enum { // NOLINT(modernize-use-using)
    CM_PROC_PC,
    CM_PROC_MVENDORID,
    CM_PROC_MARCHID,
    CM_PROC_MIMPID,
    CM_PROC_MCYCLE,
    CM_PROC_MINSTRET,
    CM_PROC_MSTATUS,
    CM_PROC_MTVEC,
    CM_PROC_MSCRATCH,
    CM_PROC_MEPC,
    CM_PROC_MCAUSE,
    CM_PROC_MTVAL,
    CM_PROC_MISA,
    CM_PROC_MIE,
    CM_PROC_MIP,
    CM_PROC_MEDELEG,
    CM_PROC_MIDELEG,
    CM_PROC_MCOUNTEREN,
    CM_PROC_STVEC,
    CM_PROC_SSCRATCH,
    CM_PROC_SEPC,
    CM_PROC_SCAUSE,
    CM_PROC_STVAL,
    CM_PROC_SATP,
    CM_PROC_SCOUNTEREN,
    CM_PROC_ILRSC,
    CM_PROC_IFLAGS,
    CM_PROC_CLINT_MTIMECMP,
    CM_PROC_HTIF_TOHOST,
    CM_PROC_HTIF_FROMHOST,
    CM_PROC_HTIF_IHALT,
    CM_PROC_HTIF_ICONSOLE,
    CM_PROC_HTIF_IYIELD,
    CM_PROC_DHD_TSTART,
    CM_PROC_DHD_TLENGTH,
    CM_PROC_DHD_DLENGTH,
    CM_PROC_DHD_HLENGTH
} CM_PROC_CSR;

/// \brief Processor state configuration
typedef struct { // NOLINT(modernize-use-using)
    uint64_t x[CM_MACHINE_X_REG_COUNT];          ///< Value of general-purpose registers
    uint64_t pc;                  ///< Value of pc
    uint64_t mvendorid;    ///< Value of mvendorid CSR
    uint64_t marchid;        ///< Value of marchid CSR
    uint64_t mimpid;          ///< Value of mimpid CSR
    uint64_t mcycle;          ///< Value of mcycle CSR
    uint64_t minstret;      ///< Value of minstret CSR
    uint64_t mstatus;        ///< Value of mstatus CSR
    uint64_t mtvec;            ///< Value of mtvec CSR
    uint64_t mscratch;      ///< Value of mscratch CSR
    uint64_t mepc;              ///< Value of mepc CSR
    uint64_t mcause;          ///< Value of mcause CSR
    uint64_t mtval;            ///< Value of mtval CSR
    uint64_t misa;              ///< Value of misa CSR
    uint64_t mie;                ///< Value of mie CSR
    uint64_t mip;                ///< Value of mip CSR
    uint64_t medeleg;        ///< Value of medeleg CSR
    uint64_t mideleg;        ///< Value of mideleg CSR
    uint64_t mcounteren;  ///< Value of mcounteren CSR
    uint64_t stvec;            ///< Value of stvec CSR
    uint64_t sscratch;      ///< Value of sscratch CSR
    uint64_t sepc;              ///< Value of sepc CSR
    uint64_t scause;          ///< Value of scause CSR
    uint64_t stval;            ///< Value of stval CSR
    uint64_t satp;              ///< Value of satp CSR
    uint64_t scounteren;  ///< Value of scounteren CSR
    uint64_t ilrsc;            ///< Value of ilrsc CSR
    uint64_t iflags;          ///< Value of iflags CSR
} cm_processor_config;


/// \brief RAM state configuration
typedef struct { // NOLINT(modernize-use-using)
    uint64_t length; ///< RAM length
    const char *image_filename; ///< RAM image file name
} cm_ram_config;

/// \brief ROM state configuration
typedef struct { // NOLINT(modernize-use-using)
    const char *bootargs; ///< Bootargs to pass to kernel
    const char *image_filename; ///< ROM image file
} cm_rom_config;

/// \brief Flash drive state configuration
typedef struct { // NOLINT(modernize-use-using)
    uint64_t start;           ///< Flash drive start position
    uint64_t length;          ///< Flash drive length
    bool shared;              ///< Target changes to drive affect image file?
    const char *image_filename; ///< Flash drive image file name
} cm_flash_drive_config;

/// \brief CLINT device state configuration
typedef struct { // NOLINT(modernize-use-using)
    uint64_t mtimecmp; ///< Value of mtimecmp CSR
} cm_clint_config;

/// \brief HTIF device state configuration
typedef struct { // NOLINT(modernize-use-using)
    uint64_t fromhost; ///< Value of fromhost CSR
    uint64_t tohost;     ///< Value of tohost CSR
    bool console_getchar;      ///< Make console getchar available?
    bool yield_progress;       ///< Make yield progress available?
    bool yield_rollup;         ///< Make yield rollup available?
} cm_htif_config;

/// \brief DHD device state configuration
typedef struct { // NOLINT(modernize-use-using)
    uint64_t tstart;           ///< Start of target physical memory range for output data
    uint64_t tlength;          ///< Length of target physical memory range for output data
    const char *image_filename; ///< Data image file name
    uint64_t dlength;          ///< Output data length CSR
    uint64_t hlength;          ///< Input hash length CSR
    uint64_t h[CM_MACHINE_DHD_H_REG_COUNT]; ///< Input hash words
} cm_dhd_config;

/// \brief Machine state configuration
typedef struct { // NOLINT(modernize-use-using)
    cm_processor_config processor;
    cm_ram_config ram;
    cm_rom_config rom;
    cm_flash_drive_config *flash_drive;
    size_t flash_drive_count;
    cm_clint_config clint;
    cm_htif_config htif;
    cm_dhd_config dhd;
} cm_machine_config;


/// \brief Merkle tree proof structure
/// \details
/// This structure holds a proof that the node spanning a log2_target_size
/// at a given address in the tree has a certain hash.
typedef struct { // NOLINT(modernize-use-using)
    uint64_t target_address;
    size_t log2_target_size;
    cm_hash target_hash;
    size_t log2_root_size;
    cm_hash root_hash;
    cm_hash* sibling_hashes;
    size_t sibling_hashes_count;
} cm_merkle_tree_proof;

/// \brief Type of state access
typedef enum { // NOLINT(modernize-use-using)
    CM_ACCESS_READ, ///< Read operation
    CM_ACCESS_WRITE, ///< Write operation
}  CM_ACCESS_TYPE;

/// \brief Type of access log
typedef struct { // NOLINT(modernize-use-using)
    bool proofs; ///< Includes proofs
    bool annotations; ///< Includes annotations
} cm_access_log_type;

/// \brief Bracket type
typedef enum { // NOLINT(modernize-use-using)
    CM_BRACKET_BEGIN,    ///< Start of scope
    CM_BRACKET_END       ///< End of scope
}  CM_BRACKET_TYPE;


/// \brief Bracket note
typedef struct { // NOLINT(modernize-use-using)
    CM_BRACKET_TYPE type;   ///< Bracket type
    uint64_t where;         ///< Where it points to in the log
    char* text;           ///< Note text
} cm_bracket_note;

/// \brief Records an access to the machine state
typedef struct { // NOLINT(modernize-use-using)
    CM_ACCESS_TYPE type; ///< Type of access
    uint64_t address;   ///< Address of access
    int log2_size;      ///< Log2 of size of access
    uint8_t* read_data; ///< Data before access
    size_t read_data_size; ///< Size of data before access in bytes
    uint8_t* written_data;  ///< Data after access (if writing)
    size_t written_data_size; ///< Size of data after access in bytes
    cm_merkle_tree_proof* proof; ///< Proof of data before access
} cm_access;

/// \brief Log of state accesses
typedef struct { // NOLINT(modernize-use-using)
    cm_access *accesses; ///< List of all accesses
    size_t accesses_count; ///< Size of list of all accesses
    cm_bracket_note *brackets; ///< Begin/End annotations
    size_t brackets_count; ///< Size of begin/end annotations
    const char **notes;  ///< Per-access annotations
    size_t notes_count; ///< Number of per-access annotations
    cm_access_log_type log_type; ///< Log type
} cm_access_log;


/// \brief DHD runtime configuration
typedef struct { // NOLINT(modernize-use-using)
    const char *source_address; ///< Address of dehash source
} cm_dhd_runtime_config;

/// \brief Concurrency runtime configuration
typedef struct { // NOLINT(modernize-use-using)
    uint64_t update_merkle_tree;
} cm_concurrency_config;

/// \brief Machine runtime configuration
typedef struct { // NOLINT(modernize-use-using)
    cm_dhd_runtime_config dhd;
    cm_concurrency_config concurrency;
} cm_machine_runtime_config;

/// \brief Machine instance handle
typedef void cm_machine; // NOLINT(modernize-use-using)


// ---------------------------------
// API function definitions
// ---------------------------------


/// \brief Create new machine config with default parameters
/// \returns Pointer to new default config object
/// \details Object acquired from this function must not be changed and
/// must be deleted with cm_delete_machine_config. To make a custom config based
/// on default config user must make a deep copy of returned object members and then
/// customize
CM_API const cm_machine_config *cm_new_default_machine_config(void);

/// \brief Delete machine config acquired from cm_new_default_machine_config
/// \returns void
CM_API void cm_delete_machine_config(const cm_machine_config *config);


/// \brief Create new machine instance from configuration
/// \param config Machine configuration. Must be pointer to valid object
/// \param runtime_config Machine runtime configuration. Must be pointer to valid object
/// \param new_machine Receives the pointer to new machine instance
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_create_machine(const cm_machine_config *config, const cm_machine_runtime_config *runtime_config,
                      cm_machine **new_machine, char **err_msg);

/// \brief Create machine instance from previously serialized directory
/// \param dir Directory where previous machine is serialized
/// \param runtime_config Machine runtime configuration. Must be pointer to valid object
/// \param new_machine Receives the pointer to new machine instance
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_load_machine(const char *dir, const cm_machine_runtime_config *runtime_config,
                                      cm_machine **new_machine, char **err_msg);


/// \brief Serialize entire state to directory
/// \param m Pointer to valid machine instance
/// \param dir Directory where the machine will be serialized
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \details The method changes machine because it updates the root hash
/// \returns 0 for success, non zero code for error
CM_API int cm_store(cm_machine *m, const char *dir, char **err_msg);


/// \brief Deletes machine instance
/// \param m Valid pointer to the existing machine instance
CM_API void cm_delete_machine(cm_machine *m);


/// \brief Runs the machine until mcycle reaches mcycle_end or the machine halts.
/// \param m Pointer to valid machine instance
/// \param mcycle_end End cycle value
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_machine_run(cm_machine *m, uint64_t mcycle_end, char **err_msg);

/// \brief Runs the machine for one cycle logging all accesses to the state.
/// \param m Pointer to valid machine instance
/// \param log_type Type of access log to generate.
/// \param one_based Use 1-based indices when reporting errors.
/// \param access_log Receives the state access log.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_step(cm_machine *m, cm_access_log_type log_type, bool one_based,
         cm_access_log** access_log, char **err_msg);

/// \brief  Deletes the instance of cm_access_log acquired from cm_step
/// \param acc_log Valid pointer to cm_access_log object
CM_API void cm_delete_access_log(cm_access_log *acc_log);


/// \brief Checks the internal consistency of an access log
/// \param log State access log to be verified
/// \param r Machine runtime configuration to use during verification. Must be pointer to valid object
/// \param one_based Use 1-based indices when reporting errors
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_verify_access_log(const cm_access_log* log, const cm_machine_runtime_config *runtime_config,
                         bool one_based, char **err_msg);

/// \brief Checks the validity of a state transition
/// \param root_hash_before State hash before step
/// \param log Step state access log
/// \param root_hash_after State hash after step
/// \param runtime_config Machine runtime configuration to use during verification. Must be pointer to valid object
/// \param one_based Use 1-based indices when reporting errors
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for successfull verification, non zero code for error
CM_API int cm_verify_state_transition(const cm_hash *root_hash_before,
                                    const cm_access_log *log, const cm_hash *root_hash_after,
                                    const cm_machine_runtime_config *runtime_config, bool one_based,
                                    char **err_msg);

/// \brief Update the Merkle tree so it matches the contents of the machine state.
/// \param m Pointer to valid machine instance
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_update_merkle_tree(cm_machine *m, char **err_msg);

/// \brief Obtains the proof for a node in the Merkle tree
/// \param m Pointer to valid machine instance
/// \param address Address of target node. Must be aligned to a 2<sup>log2_size</sup> boundary
/// \param log2_size log<sub>2</sub> of size subintended by target node.
/// Must be between 3 (for a word) and 64 (for the entire address space), inclusive
/// \param proof Receives the proof
/// proof must be deleted with the function cm_delete_proof
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
/// \details If the node is smaller than a page size, then it must lie entirely inside the same PMA range.
CM_API int cm_get_proof(const cm_machine *m, uint64_t address, int log2_size, cm_merkle_tree_proof **proof, char **err_msg);

/// \brief  Deletes the instance of cm_merkle_tree_proof acquired from cm_get_proof
/// \param proof Valid pointer to cm_merkle_tree_proof object
CM_API void cm_delete_proof(cm_merkle_tree_proof *proof);


/// \brief Obtains the root hash of the Merkle tree
/// \param m Pointer to valid machine instance
/// \param hash Valid pointer to cm_hash structure that  receives the hash.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_get_root_hash(const cm_machine *m, cm_hash *hash, char **err_msg);


/// \brief Verifies integrity of Merkle tree.
/// \param m Pointer to valid machine instance
/// \param result True if tree is self-consistent, false otherwise.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_verify_merkle_tree(const cm_machine *m, bool *result, char **err_msg);

/// \brief Read the value of any CSR
/// \param m Pointer to valid machine instance
/// \param val Receives value read from the CSR
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_csr(const cm_machine *m, CM_PROC_CSR r, uint64_t *val, char **err_msg);

/// \brief Write the value of any CSR
/// \param m Pointer to valid machine instance
/// \param w CSR to write
/// \param val Value to write
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_csr(cm_machine *m, CM_PROC_CSR w, uint64_t val, char **err_msg);

/// \brief Gets the address of any CSR
/// \param w The CSR
/// \returns The address of the specified CSR
CM_API uint64_t cm_get_csr_address(CM_PROC_CSR w);

/// \brief Read the value of a word in the machine state.
/// \param m Pointer to valid machine instance
/// \param word_address Word address (aligned to 64-bit boundary).
/// \param word_value Receives word value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
/// \warning The current implementation of this function is very slow!
CM_API int cm_read_word(const cm_machine *m, uint64_t word_address, uint64_t *word_value, char **err_msg);


/// \brief Reads a chunk of data from the machine memory.
/// \param m Pointer to valid machine instance
/// \param address Physical address to start reading.
/// \param data Receives chunk of memory.
/// \param length Size of chunk.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
/// \details The entire chunk, from \p address to \p address + \p length must
/// be inside the same PMA region. Moreover, this PMA must be a memory PMA,
/// and not a device PMA.
CM_API int cm_read_memory(const cm_machine *m, uint64_t address, unsigned char *data, uint64_t length, char **err_msg);

/// \brief Writes a chunk of data to the machine memory.
/// \param m Pointer to valid machine instance
/// \param address Physical address to start writing.
/// \param data Source for chunk of data.
/// \param length Size of chunk.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
/// \details The entire chunk, from \p address to \p address + \p length must
/// be inside the same PMA region. Moreover, this PMA must be a memory PMA,
/// and not a device PMA.
CM_API int cm_write_memory(cm_machine *m, uint64_t address, const unsigned char *data, size_t length, char **err_msg);

/// \brief Reads the value of a general-purpose register.
/// \param m Pointer to valid machine instance
/// \param i Register index. Between 0 and X_REG_COUNT-1, inclusive.
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_x(const cm_machine *m, int i, uint64_t *val, char **err_msg);

/// \brief Writes the value of a general-purpose register.
/// \param m Pointer to valid machine instance
/// \param i Register index. Between 1 and X_REG_COUNT-1, inclusive.
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_x(cm_machine *m, int i, uint64_t val, char **err_msg);

/// \brief Gets the address of a general-purpose register.
/// \param i Register index. Between 0 and X_REG_COUNT-1, inclusive.
/// \returns Address of the specified register
CM_API uint64_t cm_get_x_address(int i);

/// \brief Reads the value of the pc register.
/// \param m Pointer to valid machine instance
/// \param val Receives the value of the register
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_pc(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the pc register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_pc(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mvendorid register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mvendorid(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Reads the value of the marchid register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_marchid(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Reads the value of the mimpid register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mimpid(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Reads the value of the mcycle register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mcycle(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mcycle register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mcycle(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the minstret register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_minstret(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the minstret register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_minstret(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mstatus register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mstatus(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mstatus register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mstatus(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mtvec register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mtvec(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mtvec register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mtvec(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mscratch register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mscratch(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mscratch register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mscratch(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mepc register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mepc(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mepc register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mepc(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mcause register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mcause(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mcause register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mcause(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mtval register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mtval(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mtval register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mtval(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the misa register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_misa(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the misa register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_misa(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mie register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mie(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Reads the value of the mie register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mie(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mip register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mip(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Reads the value of the mip register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mip(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the medeleg register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_medeleg(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the medeleg register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_medeleg(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mideleg register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mideleg(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mideleg register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mideleg(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the mcounteren register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_mcounteren(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the mcounteren register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_mcounteren(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the stvec register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_stvec(const cm_machine *m, uint64_t *val, char **err_msg);


/// \brief Writes the value of the stvec register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_stvec(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the sscratch register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_sscratch(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the sscratch register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_sscratch(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the sepc register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_sepc(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the sepc register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_sepc(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the scause register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_scause(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the scause register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_scause(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the stval register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_stval(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the stval register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_stval(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the satp register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_satp(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the satp register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_satp(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the scounteren register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_scounteren(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the scounteren register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_scounteren(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the ilrsc register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_ilrsc(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of the ilrsc register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_ilrsc(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of the iflags register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_iflags(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Returns packed iflags from its component fields.
/// \param val Receives value of the register.
CM_API uint64_t cm_packed_iflags(int PRV, int Y, int H);

/// \brief Reads the value of the iflags register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_iflags(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of HTIF's tohost register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_htif_tohost(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Reads the value of the device field of HTIF's tohost register.
/// \param m Pointer to valid machine instance
/// \param val Receives the value of the field
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_htif_tohost_dev(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Reads the value of the command field of HTIF's tohost register.
/// \param m Pointer to valid machine instance
/// \param val Receives the value of the field
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_htif_tohost_cmd(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Reads the value of the data field of HTIF's tohost register.
/// \param m Pointer to valid machine instance
/// \param val Receives the value of the field
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_htif_tohost_data(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of HTIF's tohost register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_htif_tohost(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of HTIF's fromhost register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_htif_fromhost(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of HTIF's fromhost register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_htif_fromhost(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Writes the value of the data field in HTIF's fromhost register.
/// \param m Pointer to valid machine instance
/// \param val New value for the field.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_htif_fromhost_data(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of HTIF's halt register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_htif_ihalt(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of HTIF's halt register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_htif_ihalt(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of HTIF's console register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_htif_iconsole(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of HTIF's console register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_htif_iconsole(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of HTIF's yield register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_htif_iyield(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of HTIF's yield register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_htif_iyield(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of CLINT's mtimecmp register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_clint_mtimecmp(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of CLINT's mtimecmp register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_clint_mtimecmp(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of DHD's tstart register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_dhd_tstart(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of DHD's tstart register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_dhd_tstart(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of DHD's tlength register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_dhd_tlength(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of DHD's tlength register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_dhd_tlength(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of DHD's dlength register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_dhd_dlength(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of DHD's dlength register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_dhd_dlength(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of DHD's hlength register.
/// \param m Pointer to valid machine instance
/// \param val Receives value of the register.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_dhd_hlength(const cm_machine *m, uint64_t *val, char **err_msg);

/// \brief Writes the value of DHD's hlength register.
/// \param m Pointer to valid machine instance
/// \param val New register value.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_dhd_hlength(cm_machine *m, uint64_t val, char **err_msg);

/// \brief Reads the value of DHD's input hash word.
/// \param m Pointer to valid machine instance
/// \param i Index of input hash word.
/// Between 0 and DHD_H_REG_COUNT-1, inclusive
/// \param val Receives value of the hash word
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_dhd_h(const cm_machine *m, int i, uint64_t *val, char **err_msg);

/// \brief Writes the value of DHD's input hash word.
/// \param m Pointer to valid machine instance
/// \param i Index of input hash word.
/// Between 0 and DHD_H_REG_COUNT-1, inclusive.
/// \param val New value for word
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_write_dhd_h(cm_machine *m, int i, uint64_t val, char **err_msg);

/// \brief Gets the address of a DHD h register
/// \param i Register index. Between 0 and DHD_H_REG_COUNT-1, inclusive
/// \returns Address of the specified register
CM_API uint64_t cm_get_dhd_h_address(int i);

/// \brief Checks the value of the iflags_Y flag.
/// \param m Pointer to valid machine instance
/// \param val Receives the flag value
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_iflags_Y(const cm_machine *m, bool *val, char **err_msg);

/// \brief Resets the value of the iflags_Y flag.
/// \param m Pointer to valid machine instance
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_reset_iflags_Y(cm_machine *m, char **err_msg);

/// \brief Sets the iflags_Y flag.
/// \param m Pointer to valid machine instance
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_set_iflags_Y(cm_machine *m, char **err_msg);

/// \brief Checks the value of the iflags_H flag.
/// \param m Pointer to valid machine instance
/// \param val Receives the flag value
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_read_iflags_H(const cm_machine *m, bool *val, char **err_msg);

/// \brief Sets the iflags_H flag.
/// \param m Pointer to valid machine instance
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_set_iflags_H(cm_machine *m, char **err_msg);

/// \brief Dump all memory ranges to files in current working directory.
/// \param m Pointer to valid machine instance
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_dump_pmas(const cm_machine *m, char **err_msg);


/// \brief Verify if dirty page maps are consistent.
/// \param m Pointer to valid machine instance
/// \param result True if dirty page maps are consistent, false if there is an error.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_verify_dirty_page_maps(const cm_machine *m, bool *result, char** err_msg);

/// \brief Returns copy of initialization config.
/// \param m Pointer to valid machine instance
/// \param config Receives the initial configuration.
/// It should be deleted with cm_delete_machine_config.
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
/// \details Object acquired from this function must not be changed and
/// must be deleted with cm_delete_machine_config
CM_API int cm_get_initial_config(const cm_machine *m, const cm_machine_config **config, char **err_msg);


/// \brief Returns copy of default system config.
/// \param config Receives the default configuration.
/// It should be deleted with cm_delete_machine_config
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
/// \details Object acquired from this function must not be changed and
/// must be deleted with cm_delete_machine_config
CM_API int cm_get_default_config(const cm_machine_config **config, char **err_msg);

/// \brief Replaces a flash drive
/// \param m Pointer to valid machine instance
/// \param new_flash Configuration of the new flash drive
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg 
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
/// \details The machine must contain an existing flash
/// drive matching the start and length specified in new_flash
CM_API int cm_replace_flash_drive(cm_machine *m, const cm_flash_drive_config *new_flash, char **err_msg);


/// \brief Deletes the error message
/// \param err_msg Pointer to error message received from some other function
/// \details This C API is meant to be used for various language bindings.
/// Many of them could not directly call C free function,
/// so this is a convenience function for cleanup of error messages
CM_API void cm_delete_error_message(const char* err_msg);


/// \brief Deletes machine runtime config
/// \returns void
CM_API void cm_delete_machine_runtime_config(const cm_machine_runtime_config *config);

/// \brief Destroys machine
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_destroy(cm_machine *m, char **err_msg);

/// \brief Do a snapshot of the machine
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_snapshot(cm_machine *m, char **err_msg);

/// \brief Performs rollback
/// \param err_msg Receives the error message if function execution fails
/// or NULL in case of successfull function execution. In case of failure error_msg
/// must be deleted by the function caller using cm_delete_error_message
/// \returns 0 for success, non zero code for error
CM_API int cm_rollback(cm_machine *m, char **err_msg);

#ifdef __cplusplus
}
#endif

#endif //CM_C_API_H
