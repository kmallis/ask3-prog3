# # Προσομοίωση Ηλεκτρονικού Καταστήματος (E-Shop) με Sockets

Αυτή η εργασία αφορά την ανάπτυξη ενός **ηλεκτρονικού καταστήματος (E-Shop)** με χρήση **δικτυακών υποδοχών (sockets)** για την επικοινωνία μεταξύ ενός διακομιστή (server) και πολλών πελατών (clients). Οι πελάτες στέλνουν αιτήματα παραγγελίας για προϊόντα, και ο διακομιστής επεξεργάζεται τις παραγγελίες, διαχειρίζεται τη διαθεσιμότητα των προϊόντων και καταγράφει στατιστικά στοιχεία.

## Ζητούμενα 
- **Υλοποίηση επικοινωνίας server-client** μέσω sockets (TCP/IP).
- **Διαχείριση προϊόντων** με περιορισμένη διαθεσιμότητα.
- **Επεξεργασία παραγγελιών** από πολλαπλούς πελάτες με χρονική καθυστέρηση.
- **Αποστολή αποτελεσμάτων** προς τους πελάτες (επιτυχής ή αποτυχημένη παραγγελία).
- **Τελική αναφορά** με στατιστικά στοιχεία για τις παραγγελίες.

---

## Υλοποίηση
### 🔹 Διακομιστής (`server.c`)
- Δημιουργεί ένα **socket** και το συνδέει σε μια συγκεκριμένη **θύρα (port)**.
- Περιμένει **συνδέσεις από πελάτες** (clients) μέσω `accept()`.
- Διαβάζει το αίτημα παραγγελίας του πελάτη μέσω `recv()`.
- Ελέγχει αν το προϊόν είναι διαθέσιμο:
  - Αν υπάρχει διαθεσιμότητα, **μειώνει το απόθεμα** και καταγράφει την παραγγελία ως επιτυχή.
  - Αν δεν υπάρχει, ενημερώνει τον πελάτη για αποτυχία.
- Στέλνει την απάντηση στον πελάτη μέσω `send()`.
- Όταν ολοκληρωθούν όλες οι παραγγελίες, εκτυπώνει μια **αναφορά με στατιστικά**.

### 🔹 Πελάτης (`client.c`)
- Δημιουργεί ένα **socket** και συνδέεται στον διακομιστή μέσω `connect()`.
- Υποβάλλει **10 τυχαίες παραγγελίες** χρησιμοποιώντας `send()`.
- Περιμένει απάντηση από τον διακομιστή μέσω `recv()` και εμφανίζει το μήνυμα.
- Μεταξύ των παραγγελιών υπάρχει **χρονική καθυστέρηση 1 δευτερολέπτου** (`sleep(1)`).
- Όταν ολοκληρωθούν οι παραγγελίες, ο πελάτης **τερματίζει τη λειτουργία του**.

---

## Εκτέλεση

Χρησιμοποιούμε το **Makefile** για να μεταγλωττίσουμε εύκολα το πρόγραμμα:
```bash
make
```
Αυτό θα δημιουργήσει τα εκτελέσιμα αρχεία `server` και `client`.

1. **Εκκίνηση του διακομιστή**:
   ```bash
   ./server
   ```
2. **Εκκίνηση των πελατών** (σε διαφορετικά τερματικά):
   ```bash
   ./client
   ```
Κάθε πελάτης θα υποβάλλει **10 παραγγελίες** και θα εμφανίζει τα αποτελέσματα. Πρέπει στο σύνολο να γίνουν 5 πελάτες για να εκτυπωθεί η συνολική αναφορά στον server. Άρα πρέπει να εκτελεσθεί 5 φορές ο κώδικας του client.

---

## Αναφορά Δεδομένων
Όταν ολοκληρωθούν όλες οι παραγγελίες, ο διακομιστής θα εμφανίσει μια **αναφορά στατιστικών** με:
✔️ **Συνολικό αριθμό παραγγελιών**
✔️ **Επιτυχείς και αποτυχημένες παραγγελίες**
✔️ **Λίστα πελατών που δεν εξυπηρετήθηκαν** (με τον αριθμό τους)
✔️ **Συνολικό τζίρο** του καταστήματος
