# Smart Library Management System (SLMS)

A C++ console-based library management system that supports multiple user roles (Admin, Librarian, Member) with features for book cataloguing, borrowing, reservations, and notifications.

## Features

- **Admin**: Manage users, add/remove librarians and members, view all records.
- **Librarian**: Add/remove books, manage borrowing and returns.
- **Member**: Search books, borrow/return/reserve books, receive notifications.
- Password encoding using XOR cipher.
- Reservation expiry checks (3-day window).

## Default Accounts

| Role       | Username    | Password  |
|------------|-------------|-----------|
| Admin      | `admin`     | `admin123`|
| Librarian  | `librarian` | `lib123`  |

## Build & Run

```bash
make
./slms
```

## Screenshot

![SLMS Screenshot](Screenshot%202026-02-24%20at%2020.15.34.png)

## Demo Video

<video src="Videos%20_%20Library%20_%20Loom%20-%2013%20March%202026.mp4" controls width="100%">
  Your browser does not support the video tag.
</video>
