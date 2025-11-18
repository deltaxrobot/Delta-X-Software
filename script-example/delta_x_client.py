#!/usr/bin/env python3
import argparse
import socket
import tkinter as tk
from tkinter import ttk, messagebox

class DeltaXClient:
    def __init__(self, master, host, port):
        self.master = master
        self.host = host
        self.port = port
        self.sock = None

        master.title("Delta X Variable Client")
        master.resizable(False, False)

        main = ttk.Frame(master, padding=10)
        main.grid(column=0, row=0, sticky="nsew")

        ttk.Label(main, text=f"Server: {host}:{port}").grid(column=0, row=0, columnspan=2, sticky="w")

        ttk.Label(main, text="Variable name (e.g. #project0.MyVar):").grid(column=0, row=1, sticky="w")
        self.var_entry = ttk.Entry(main, width=40)
        self.var_entry.grid(column=0, row=2, columnspan=2, sticky="we", pady=(0, 8))
        self.var_entry.insert(0, "#project0.MyVar")

        ttk.Label(main, text="Value (for write):").grid(column=0, row=3, sticky="w")
        self.val_entry = ttk.Entry(main, width=40)
        self.val_entry.grid(column=0, row=4, columnspan=2, sticky="we", pady=(0, 8))

        self.read_btn = ttk.Button(main, text="Read", command=self.read_var)
        self.read_btn.grid(column=0, row=5, sticky="we", pady=4)
        self.write_btn = ttk.Button(main, text="Write", command=self.write_var)
        self.write_btn.grid(column=1, row=5, sticky="we", pady=4)

        ttk.Label(main, text="Result / log:").grid(column=0, row=6, columnspan=2, sticky="w", pady=(8,0))
        self.log = tk.Text(main, width=50, height=8, state="disabled")
        self.log.grid(column=0, row=7, columnspan=2, sticky="nsew")

        self.connect()

    def connect(self):
        try:
            self.sock = socket.create_connection((self.host, self.port), timeout=5)
            _ = self.sock.recv(64)  # greeting "deltax\n"
            self.sock.sendall(b"ClientName=MinimalClient\n")
            self.log_message(f"Connected to {self.host}:{self.port}")
        except OSError as e:
            messagebox.showerror("Connection error", str(e))
            self.master.destroy()

    def log_message(self, text):
        self.log.configure(state="normal")
        self.log.insert("end", text + "\n")
        self.log.configure(state="disabled")
        self.log.see("end")

    def write_var(self):
        name = self.var_entry.get().strip()
        value = self.val_entry.get().strip()
        if not name or not value:
            messagebox.showwarning("Input", "Variable name and value are required.")
            return
        msg = f"{name} = {value}\n".encode("utf-8")
        try:
            self.sock.sendall(msg)
            self.log_message(f"Sent: {msg.decode().strip()}")
        except OSError as e:
            messagebox.showerror("Socket error", str(e))

    def read_var(self):
        name = self.var_entry.get().strip()
        if not name.startswith("#"):
            messagebox.showwarning("Input", "Reading requires variable name to start with '#'.")
            return
        msg = f"{name}\n".encode("utf-8")
        try:
            self.sock.sendall(msg)
            data = self.sock.recv(4096).decode("utf-8").strip()
            self.log_message(f"{name} -> {data}")
        except OSError as e:
            messagebox.showerror("Socket error", str(e))

def main():
    parser = argparse.ArgumentParser(description="Minimal Delta X variable client")
    parser.add_argument("--host", default="127.0.0.1", help="Delta X host")
    parser.add_argument("--port", type=int, default=8844, help="Delta X port")
    args = parser.parse_args()

    root = tk.Tk()
    DeltaXClient(root, args.host, args.port)
    root.mainloop()

if __name__ == "__main__":
    main()
