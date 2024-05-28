import tkinter as tk
from tkinter import ttk
import tkinter.font as font

# Create a custom style for the button
style = ttk.Style()
style.theme_use("clam")  # Use the "clam" theme as a base
style.configure("TButton", background="#800080", foreground="white", font=("Helvetica", 12, "bold"))

# Create main window
root = tk.Tk()
root.title("Order Display")

# Set the background color for the main window
root.configure(bg="#2F2F2F")

# Create a frame to display cards
card_frame = tk.Frame(root, width=820, height=500, bg="#2F2F2F")
card_frame.pack(fill=tk.BOTH, expand=True)

# Define the display_orders function
def display_orders():
    """Reads orders from buffer.txt and displays them in a listbox."""

    # Clear existing orders
    for widget in card_frame.winfo_children():
        widget.destroy()

    try:
        with open("buffer.txt", "r") as f:
            orders = f.read().split("~\n")

        for i, order in enumerate(orders):
            lines = [line.strip() for line in order.splitlines()]  # Remove extra newline characters
            if lines:  # Added check to ensure the list has at least one element
                try:
                    name_surname, phone = lines[0].split(" +")
                except ValueError:
                    # Handle the case where the name and phone are not separated by " +"
                    name_surname = lines[0]
                    phone = ""

                items = lines[1:-1]  # Exclude the last line (total price)
                total_price = lines[-1].split()[0]

                # Create a card for the order
                card = tk.Canvas(card_frame, width=800, height=200, bg="#2F2F2F", relief="solid", borderwidth=2)
                card.pack(fill=tk.BOTH, expand=True, padx=10, pady=100)

                # Add a header to the card
                header_font = font.Font(family="Helvetica", size=14, weight="bold")
                header = tk.Label(card, text=f"Order {i+1}: {name_surname}, {phone}", font=header_font, bg="#2F2F2F", fg="white")
                header.place(relx=0.5, rely=0.1, anchor=tk.CENTER)

                # Add order items to the card
                y_pos = 50
                for item in items:
                    item_label = tk.Label(card, text=f"  {item}", font=("Helvetica", 12), bg="#2F2F2F", fg="white", anchor="nw")
                    item_label.place(relx=0.02, rely=y_pos/200, anchor=tk.NW)
                    y_pos += len(item.split()) * 15

                # Add total price to the card
                total_price_label = tk.Label(card, text=f"Total price: {total_price} rub", font=("Helvetica", 12), bg="#2F2F2F", fg="white")
                total_price_label.place(relx=0.5, rely=0.9, anchor=tk.CENTER)

                # Adjust the card size based on the content
                card_width = 500
                card_height = header.winfo_height() + total_price_label.winfo_height() + (len(items) * (item_label.winfo_height() + 50)) + 20
                card.config(width=card_width, height=card_height)

    except FileNotFoundError:
        tk.Label(card_frame, text="No orders found in buffer.txt.", font=("Helvetica", 12), bg="#2F2F2F", fg="white").pack(pady=10)

# Create the button
display_button = ttk.Button(root, text="Display Orders", command=display_orders)
display_button.pack(pady=10)

# Run the application
root.mainloop()