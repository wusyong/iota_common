use bee_crypto::{Kerl, Sponge};
use bee_ternary::{Trits};
use libc::size_t;
use std::slice;

#[no_mangle]
pub unsafe extern "C" fn rust_kerl(trits: *mut i8, len: size_t) {
    let mut kerl = Kerl::default();
    let trits = Trits::from_raw_unchecked(slice::from_raw_parts(trits, len as usize), len as usize);

    kerl.absorb(&trits).unwrap();
    let _ = kerl.squeeze();
}