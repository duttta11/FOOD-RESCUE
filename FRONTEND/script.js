/* ==========================================================================
   FoodRescue — Modern Startup Frontend Application (JavaScript)
   ========================================================================== */

// Dynamic API host detection (protects against WebKit IPv6 ::1 loopback drops and file:// protocol)
function getApiBase() {
    if (window.location.protocol === "file:") {
        return "http://127.0.0.1:8080";
    }
    if (window.location.hostname === "localhost") {
        return `http://127.0.0.1:${window.location.port || '8080'}`;
    }
    if (window.location.port && window.location.port !== "8080") {
        return "http://127.0.0.1:8080";
    }
    return "";
}

let API_BASE = getApiBase();

// Global State
let currentUser = null;
let currentRole = null; // "donor" or "ngo"
let currentAuthRole = "donor";
let currentAuthMode = "login"; // "login" or "register"

// ================= API WRAPPER =================
async function apiRequest(endpoint, method = "GET", body = null) {
    const token = localStorage.getItem("foodrescue_token");
    const headers = {
        "Content-Type": "application/json"
    };

    if (token) {
        headers["Authorization"] = `Bearer ${token}`;
    }

    const options = {
        method,
        headers
    };

    if (body) {
        options.body = JSON.stringify(body);
    }

    let url = `${API_BASE}${endpoint}`;
    let response;

    try {
        response = await fetch(url, options);
    } catch (primaryErr) {
        // Fallback: If primary fetch fails (e.g. localhost IPv6 ::1 issue), retry via explicit 127.0.0.1
        if (!url.includes("127.0.0.1:8080")) {
            console.warn(`[FoodRescue] Primary fetch to ${url} failed. Retrying via http://127.0.0.1:8080...`);
            try {
                API_BASE = "http://127.0.0.1:8080";
                url = `${API_BASE}${endpoint}`;
                response = await fetch(url, options);
            } catch (fallbackErr) {
                console.error("[FoodRescue] Fallback fetch failed:", fallbackErr);
                throw new Error("Unable to connect to backend server. Please verify the server is running.");
            }
        } else {
            console.error("[FoodRescue] Fetch failed:", primaryErr);
            throw new Error("Unable to connect to backend server. Please verify the server is running.");
        }
    }

    let data;
    try {
        data = await response.json();
    } catch (parseErr) {
        throw new Error("Server returned an invalid response.");
    }

    if (!response.ok) {
        throw new Error(data.error || "An error occurred during request.");
    }

    return data;
}

// ================= TOAST NOTIFICATIONS =================
function showToast(type, message) {
    const container = document.getElementById("toastContainer");
    if (!container) return;

    const toast = document.createElement("div");
    toast.className = `toast ${type === "error" ? "toast-error" : type === "warning" ? "toast-warning" : ""}`;
    
    const icon = type === "error" ? "❌" : type === "warning" ? "⚠️" : "✅";
    toast.innerHTML = `
        <span style="font-size: 1.1rem;">${icon}</span>
        <div style="flex: 1;">${escapeHTML(message)}</div>
    `;

    container.appendChild(toast);

    setTimeout(() => {
        toast.style.opacity = "0";
        toast.style.transform = "translateX(40px)";
        toast.style.transition = "all 0.3s ease";
        setTimeout(() => toast.remove(), 300);
    }, 4000);
}

function escapeHTML(str) {
    if (!str) return "";
    return String(str)
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;")
        .replace(/"/g, "&quot;")
        .replace(/'/g, "&#039;");
}

// ================= VIEW SWITCHER =================
function showView(viewId) {
    document.querySelectorAll(".view-section").forEach(view => {
        view.classList.remove("active");
    });

    const target = document.getElementById(viewId);
    if (target) {
        target.classList.add("active");
        window.scrollTo({ top: 0, behavior: "smooth" });
    }
}

// ================= AUTH MODAL LOGIC =================
function openAuthModal(role = "donor", mode = "login") {
    currentAuthRole = role;
    currentAuthMode = mode;

    selectAuthRole(role);
    setAuthMode(mode);

    document.getElementById("authModal").classList.add("active");
}

function closeAuthModal() {
    document.getElementById("authModal").classList.remove("active");
}

function closeAuthModalOnBackdrop(event) {
    if (event.target.id === "authModal") {
        closeAuthModal();
    }
}

function selectAuthRole(role) {
    currentAuthRole = role;

    document.getElementById("roleTabDonor").classList.toggle("active", role === "donor");
    document.getElementById("roleTabNgo").classList.toggle("active", role === "ngo");

    document.getElementById("donorAuthBlock").classList.toggle("hidden", role !== "donor");
    document.getElementById("ngoAuthBlock").classList.toggle("hidden", role !== "ngo");
}

function setAuthMode(mode) {
    currentAuthMode = mode;
    const isLogin = mode === "login";

    document.getElementById("authModePrompt").textContent = isLogin ? "Don't have an account?" : "Already have an account?";
    document.getElementById("authModeToggleBtn").textContent = isLogin ? "Create Account" : "Sign In";

    if (currentAuthRole === "donor") {
        document.getElementById("donorLoginForm").classList.toggle("hidden", !isLogin);
        document.getElementById("donorRegisterForm").classList.toggle("hidden", isLogin);
    } else {
        document.getElementById("ngoLoginForm").classList.toggle("hidden", !isLogin);
        document.getElementById("ngoRegisterForm").classList.toggle("hidden", isLogin);
    }
}

function toggleAuthMode() {
    setAuthMode(currentAuthMode === "login" ? "register" : "login");
}

// ================= AUTHENTICATION HANDLERS =================
async function handleDonorLogin(event) {
    event.preventDefault();
    const email = document.getElementById("dLoginEmail").value.trim().toLowerCase();
    const password = document.getElementById("dLoginPassword").value;
    const btn = document.getElementById("btnDonorLogin");

    btn.disabled = true;
    btn.textContent = "Signing In...";

    try {
        const data = await apiRequest("/api/auth/donor/login", "POST", { email, password });
        localStorage.setItem("foodrescue_token", data.token);
        currentUser = data.user;
        currentRole = "donor";

        closeAuthModal();
        showToast("success", `Welcome back, ${currentUser.name}!`);
        setupDonorDashboard();
    } catch (err) {
        showToast("error", err.message);
    } finally {
        btn.disabled = false;
        btn.textContent = "Sign In";
    }
}

async function handleDonorRegister(event) {
    event.preventDefault();
    const name = document.getElementById("dRegName").value.trim();
    const email = document.getElementById("dRegEmail").value.trim().toLowerCase();
    const phone = document.getElementById("dRegPhone").value.trim();
    const address = document.getElementById("dRegAddress").value.trim();
    const password = document.getElementById("dRegPassword").value;
    const confirm = document.getElementById("dRegConfirmPassword").value;
    const btn = document.getElementById("btnDonorRegister");

    if (password !== confirm) {
        showToast("error", "Passwords do not match.");
        return;
    }

    btn.disabled = true;
    btn.textContent = "Creating Account...";

    try {
        const data = await apiRequest("/api/auth/donor/register", "POST", {
            name, email, phone, address, password
        });
        localStorage.setItem("foodrescue_token", data.token);
        currentUser = data.user;
        currentRole = "donor";

        closeAuthModal();
        showToast("success", `Account created successfully! Welcome, ${currentUser.name}!`);
        setupDonorDashboard();
    } catch (err) {
        showToast("error", err.message);
    } finally {
        btn.disabled = false;
        btn.textContent = "Create Donor Account";
    }
}

async function handleNgoLogin(event) {
    event.preventDefault();
    const email = document.getElementById("nLoginEmail").value.trim().toLowerCase();
    const password = document.getElementById("nLoginPassword").value;
    const btn = document.getElementById("btnNgoLogin");

    btn.disabled = true;
    btn.textContent = "Signing In...";

    try {
        const data = await apiRequest("/api/auth/ngo/login", "POST", { email, password });
        localStorage.setItem("foodrescue_token", data.token);
        currentUser = data.user;
        currentRole = "ngo";

        closeAuthModal();
        showToast("success", `Welcome back, ${currentUser.name}!`);
        setupNgoDashboard();
    } catch (err) {
        showToast("error", err.message);
    } finally {
        btn.disabled = false;
        btn.textContent = "Sign In";
    }
}

async function handleNgoRegister(event) {
    event.preventDefault();
    const name = document.getElementById("nRegName").value.trim();
    const email = document.getElementById("nRegEmail").value.trim().toLowerCase();
    const phone = document.getElementById("nRegPhone").value.trim();
    const location = document.getElementById("nRegLocation").value.trim();
    const capacity = parseInt(document.getElementById("nRegCapacity").value, 10);
    const password = document.getElementById("nRegPassword").value;
    const confirm = document.getElementById("nRegConfirmPassword").value;
    const btn = document.getElementById("btnNgoRegister");

    if (password !== confirm) {
        showToast("error", "Passwords do not match.");
        return;
    }

    btn.disabled = true;
    btn.textContent = "Registering NGO...";

    try {
        const data = await apiRequest("/api/auth/ngo/register", "POST", {
            name, email, phone, location, capacity, password
        });
        localStorage.setItem("foodrescue_token", data.token);
        currentUser = data.user;
        currentRole = "ngo";

        closeAuthModal();
        showToast("success", `NGO Registered successfully! Welcome, ${currentUser.name}!`);
        setupNgoDashboard();
    } catch (err) {
        showToast("error", err.message);
    } finally {
        btn.disabled = false;
        btn.textContent = "Register NGO Account";
    }
}

async function handleLogout() {
    try {
        await apiRequest("/api/auth/logout", "POST");
    } catch (e) {
        // proceed anyway
    }

    localStorage.removeItem("foodrescue_token");
    currentUser = null;
    currentRole = null;
    showToast("success", "You have been safely signed out.");
    showView("landingView");
    loadLandingStats();
}

// ================= DONOR DASHBOARD LOGIC =================
function setupDonorDashboard() {
    showView("donorDashboardView");

    // Populate Sidebar
    document.getElementById("donorSidebarName").textContent = currentUser.name;
    document.getElementById("donorSidebarEmail").textContent = currentUser.email;
    document.getElementById("donorSidebarInitials").textContent = currentUser.name.charAt(0).toUpperCase();
    document.getElementById("donorHeaderGreeting").textContent = `Welcome, ${currentUser.name}!`;

    // Pre-fill donation pickup location
    const pickupField = document.getElementById("pickupAddress");
    if (pickupField && currentUser.address) {
        pickupField.value = currentUser.address;
    }

    switchDonorTab("donor-overview");
}

function switchDonorTab(tabId) {
    // Nav items
    document.querySelectorAll("#donorDashboardView .sidebar-nav .nav-item").forEach(item => {
        item.classList.toggle("active", item.dataset.tab === tabId);
    });

    // Content Panes
    document.querySelectorAll("#donorDashboardView .tab-pane").forEach(pane => {
        pane.classList.toggle("active", pane.id === `tab-${tabId}`);
    });

    // Tab-specific loads
    if (tabId === "donor-overview") {
        loadDonorOverview();
    } else if (tabId === "donor-donations") {
        loadDonorDonations();
    } else if (tabId === "donor-deliveries") {
        loadDonorDeliveries();
    }
}

async function loadDonorOverview() {
    try {
        const data = await apiRequest("/api/donor/overview");
        document.getElementById("dStatTotalDonations").textContent = data.totalDonations;
        document.getElementById("dStatAvailableDonations").textContent = data.availableDonations;
        document.getElementById("dStatMatchedDonations").textContent = data.matchedDonations;
        document.getElementById("dStatCompletedDeliveries").textContent = data.completedDeliveries;

        // Also load deliveries preview
        loadDonorDeliveriesPreview();
    } catch (err) {
        showToast("error", "Could not load donor overview.");
    }
}

async function handleCreateDonation(event) {
    event.preventDefault();
    const foodName = document.getElementById("foodName").value.trim();
    const quantity = parseInt(document.getElementById("foodQuantity").value, 10);
    const expiryDate = document.getElementById("expiryDate").value.trim();
    const pickupAddress = document.getElementById("pickupAddress").value.trim();
    const btn = document.getElementById("btnSubmitDonation");

    btn.disabled = true;
    btn.textContent = "Matching with Verified NGOs...";

    try {
        const data = await apiRequest("/api/donor/donations", "POST", {
            foodName, quantity, expiryDate, pickupAddress
        });

        if (data.matchesCreated > 0) {
            showToast("success", `🎉 Instant Match! Paired with an NGO and volunteer assigned.`);
        } else {
            showToast("success", `Donation created! Standing by for internal matching.`);
        }

        // Reset form
        document.getElementById("foodName").value = "";
        document.getElementById("foodQuantity").value = "";
        document.getElementById("expiryDate").value = "";

        switchDonorTab("donor-deliveries");
    } catch (err) {
        showToast("error", err.message);
    } finally {
        btn.disabled = false;
        btn.textContent = "Submit Donation for Matching";
    }
}

async function loadDonorDonations() {
    const tbody = document.getElementById("donorDonationsTableBody");
    tbody.innerHTML = `<tr><td colspan="6" class="text-center">Loading donations...</td></tr>`;

    try {
        const data = await apiRequest("/api/donor/donations");
        const list = data.donations || [];

        if (list.length === 0) {
            tbody.innerHTML = `<tr><td colspan="6" class="text-center empty-text">No donations yet. Click "Donate Food" to start rescuing meals.</td></tr>`;
            return;
        }

        tbody.innerHTML = list.map(item => `
            <tr>
                <td><strong>#${item.id}</strong></td>
                <td><strong>${escapeHTML(item.foodName)}</strong></td>
                <td>${item.quantity} meals</td>
                <td>${escapeHTML(item.expiryDate)}</td>
                <td>${escapeHTML(item.pickupAddress)}</td>
                <td>
                    <span class="badge ${item.available ? (item.quantity > 0 ? 'badge-primary' : 'badge-transit') : 'badge-delivered'}">
                        ${escapeHTML(item.status)}
                    </span>
                </td>
            </tr>
        `).join("");
    } catch (err) {
        tbody.innerHTML = `<tr><td colspan="6" class="text-center empty-text" style="color:var(--danger)">Failed to load donations.</td></tr>`;
    }
}

async function loadDonorDeliveries() {
    const container = document.getElementById("donorDeliveriesContainer");
    container.innerHTML = `<p class="empty-text">Loading deliveries...</p>`;

    try {
        const data = await apiRequest("/api/donor/deliveries");
        const deliveries = data.deliveries || [];

        // Update badge
        document.getElementById("donorDeliveriesCountBadge").textContent = deliveries.length;

        if (deliveries.length === 0) {
            container.innerHTML = `
                <div class="empty-text">
                    <p style="font-size:1.1rem; margin-bottom:8px;">No active or past deliveries.</p>
                    <p class="text-muted">When your food donation is matched with an NGO, your delivery tracking will appear here.</p>
                </div>
            `;
            return;
        }

        container.innerHTML = deliveries.map(del => renderDeliveryCard(del, "donor")).join("");
    } catch (err) {
        container.innerHTML = `<p class="empty-text" style="color:var(--danger)">Failed to load delivery records.</p>`;
    }
}

async function loadDonorDeliveriesPreview() {
    const preview = document.getElementById("donorActiveDeliveriesPreview");
    try {
        const data = await apiRequest("/api/donor/deliveries");
        const deliveries = data.deliveries || [];
        const activeList = deliveries.filter(d => d.statusCode >= 1 && d.statusCode <= 3);

        if (activeList.length === 0) {
            preview.innerHTML = `<p class="empty-text">No active deliveries in transit right now.</p>`;
            return;
        }

        preview.innerHTML = activeList.slice(0, 2).map(del => renderDeliveryCard(del, "donor")).join("");
    } catch (err) {
        preview.innerHTML = `<p class="empty-text">Unable to preview deliveries.</p>`;
    }
}

// ================= NGO DASHBOARD LOGIC =================
function setupNgoDashboard() {
    showView("ngoDashboardView");

    // Populate Sidebar
    document.getElementById("ngoSidebarName").textContent = currentUser.name;
    document.getElementById("ngoSidebarEmail").textContent = currentUser.email;
    document.getElementById("ngoSidebarInitials").textContent = currentUser.name.charAt(0).toUpperCase();
    document.getElementById("ngoHeaderGreeting").textContent = `Welcome, ${currentUser.name}!`;

    switchNgoTab("ngo-overview");
}

function switchNgoTab(tabId) {
    document.querySelectorAll("#ngoDashboardView .sidebar-nav .nav-item").forEach(item => {
        item.classList.toggle("active", item.dataset.tab === tabId);
    });

    document.querySelectorAll("#ngoDashboardView .tab-pane").forEach(pane => {
        pane.classList.toggle("active", pane.id === `tab-${tabId}`);
    });

    if (tabId === "ngo-overview") {
        loadNgoOverview();
    } else if (tabId === "ngo-requirements") {
        loadNgoRequirements();
    } else if (tabId === "ngo-deliveries") {
        loadNgoDeliveries();
    }
}

async function loadNgoOverview() {
    try {
        const data = await apiRequest("/api/ngo/overview");
        document.getElementById("nStatTotalRequirements").textContent = data.totalRequirements;
        document.getElementById("nStatPendingRequirements").textContent = data.pendingRequirements;
        document.getElementById("nStatFulfilledRequirements").textContent = data.fulfilledRequirements;
        document.getElementById("nStatCompletedDeliveries").textContent = data.completedDeliveries;
        document.getElementById("nStatCapacity").textContent = data.capacity;

        loadNgoDeliveriesPreview();
    } catch (err) {
        showToast("error", "Could not load NGO overview.");
    }
}

async function handleCreateRequirement(event) {
    event.preventDefault();
    const foodType = document.getElementById("reqFoodType").value.trim();
    const quantity = parseInt(document.getElementById("reqQuantity").value, 10);
    const urgency = parseInt(document.getElementById("reqUrgency").value, 10);
    const instructions = document.getElementById("reqInstructions").value.trim();
    const btn = document.getElementById("btnSubmitRequirement");

    btn.disabled = true;
    btn.textContent = "Scanning Available Donations...";

    try {
        const data = await apiRequest("/api/ngo/requirements", "POST", {
            foodType, quantity, urgency, instructions
        });

        if (data.matchesCreated > 0) {
            showToast("success", `🎉 Requirement Matched! A volunteer is dispatched.`);
        } else {
            showToast("success", `Requirement submitted! Added to high-priority rescue queue.`);
        }

        document.getElementById("reqFoodType").value = "";
        document.getElementById("reqQuantity").value = "";

        switchNgoTab("ngo-deliveries");
    } catch (err) {
        showToast("error", err.message);
    } finally {
        btn.disabled = false;
        btn.textContent = "Submit Requirement for Internal Match";
    }
}

async function loadNgoRequirements() {
    const tbody = document.getElementById("ngoRequirementsTableBody");
    tbody.innerHTML = `<tr><td colspan="5" class="text-center">Loading requirements...</td></tr>`;

    try {
        const data = await apiRequest("/api/ngo/requirements");
        const list = data.requirements || [];

        if (list.length === 0) {
            tbody.innerHTML = `<tr><td colspan="5" class="text-center empty-text">No requirements logged yet. Click "Request Food" to ask for meals.</td></tr>`;
            return;
        }

        tbody.innerHTML = list.map(item => `
            <tr>
                <td><strong>#${item.id}</strong></td>
                <td><strong>${escapeHTML(item.foodType)}</strong></td>
                <td>${item.quantity} meals</td>
                <td>
                    <span class="badge badge-urgency-${item.urgency}">
                        Level ${item.urgency} Urgency
                    </span>
                </td>
                <td>
                    <span class="badge ${item.status === 'Fulfilled' ? 'badge-delivered' : 'badge-picked-up'}">
                        ${escapeHTML(item.status)}
                    </span>
                </td>
            </tr>
        `).join("");
    } catch (err) {
        tbody.innerHTML = `<tr><td colspan="5" class="text-center empty-text" style="color:var(--danger)">Failed to load requirements.</td></tr>`;
    }
}

async function loadNgoDeliveries() {
    const container = document.getElementById("ngoDeliveriesContainer");
    container.innerHTML = `<p class="empty-text">Loading incoming deliveries...</p>`;

    try {
        const data = await apiRequest("/api/ngo/deliveries");
        const deliveries = data.deliveries || [];

        document.getElementById("ngoDeliveriesCountBadge").textContent = deliveries.length;

        if (deliveries.length === 0) {
            container.innerHTML = `
                <div class="empty-text">
                    <p style="font-size:1.1rem; margin-bottom:8px;">No incoming deliveries at this time.</p>
                    <p class="text-muted">When surplus food is matched to your shelter, the dispatch status and assigned volunteer will appear here.</p>
                </div>
            `;
            return;
        }

        container.innerHTML = deliveries.map(del => renderDeliveryCard(del, "ngo")).join("");
    } catch (err) {
        container.innerHTML = `<p class="empty-text" style="color:var(--danger)">Failed to load deliveries.</p>`;
    }
}

async function loadNgoDeliveriesPreview() {
    const preview = document.getElementById("ngoActiveDeliveriesPreview");
    try {
        const data = await apiRequest("/api/ngo/deliveries");
        const deliveries = data.deliveries || [];
        const activeList = deliveries.filter(d => d.statusCode >= 1 && d.statusCode <= 3);

        if (activeList.length === 0) {
            preview.innerHTML = `<p class="empty-text">No incoming rescues in transit right now.</p>`;
            return;
        }

        preview.innerHTML = activeList.slice(0, 2).map(del => renderDeliveryCard(del, "ngo")).join("");
    } catch (err) {
        preview.innerHTML = `<p class="empty-text">Unable to preview deliveries.</p>`;
    }
}

// ================= RENDER DELIVERY CARD (SHARED COMPONENT) =================
function renderDeliveryCard(del, userRole) {
    const statusCodes = {
        0: { name: "Pending", badgeClass: "badge-cancelled" },
        1: { name: "Assigned", badgeClass: "badge-assigned" },
        2: { name: "Picked Up", badgeClass: "badge-picked-up" },
        3: { name: "In Transit", badgeClass: "badge-transit" },
        4: { name: "Delivered", badgeClass: "badge-delivered" },
        5: { name: "Cancelled", badgeClass: "badge-cancelled" }
    };

    const currentCode = del.statusCode;
    const progressWidth = currentCode === 1 ? "0%" : currentCode === 2 ? "33%" : currentCode === 3 ? "66%" : currentCode === 4 ? "100%" : "0%";

    const otherPartyLabel = userRole === "donor" ? "Matched NGO" : "Food Donor";
    const otherPartyValue = userRole === "donor" ? (del.ngoName || "Verified Relief Shelter") : (del.donorName || "Food Donor");
    const otherPartySub = userRole === "donor" ? `Destination: ${del.deliveryLocation}` : `Contact: ${del.donorPhone || "-"}`;

    let nextActionBtn = "";
    if (currentCode >= 1 && currentCode <= 3) {
        const nextLabels = {
            1: "Simulate 'Picked Up'",
            2: "Simulate 'In Transit'",
            3: "Mark 'Delivered'"
        };
        nextActionBtn = `
            <button class="btn btn-sm btn-outline" onclick="advanceDeliveryStatus(${del.deliveryId})">
                🚀 ${nextLabels[currentCode]}
            </button>
        `;
    }

    return `
        <div class="delivery-card">
            <div class="delivery-header">
                <div class="delivery-meta">
                    <span class="delivery-id-tag">Mission #${del.deliveryId}</span>
                    <span class="delivery-food-tag">🍲 ${escapeHTML(del.foodName)}</span>
                </div>
                <span class="badge ${statusCodes[currentCode]?.badgeClass || 'badge-assigned'}">
                    ● ${escapeHTML(del.status)}
                </span>
            </div>

            <!-- Stepper Progress Tracker -->
            <div class="delivery-stepper">
                <div class="delivery-stepper-progress" style="width: ${progressWidth};"></div>

                <div class="step-node ${currentCode >= 1 ? 'completed' : ''} ${currentCode === 1 ? 'active' : ''}">
                    <div class="step-circle">${currentCode > 1 ? '✓' : '1'}</div>
                    <span class="step-label">Assigned</span>
                </div>
                <div class="step-node ${currentCode >= 2 ? 'completed' : ''} ${currentCode === 2 ? 'active' : ''}">
                    <div class="step-circle">${currentCode > 2 ? '✓' : '2'}</div>
                    <span class="step-label">Picked Up</span>
                </div>
                <div class="step-node ${currentCode >= 3 ? 'completed' : ''} ${currentCode === 3 ? 'active' : ''}">
                    <div class="step-circle">${currentCode > 3 ? '✓' : '3'}</div>
                    <span class="step-label">In Transit</span>
                </div>
                <div class="step-node ${currentCode >= 4 ? 'completed' : ''} ${currentCode === 4 ? 'active' : ''}">
                    <div class="step-circle">${currentCode >= 4 ? '✓' : '4'}</div>
                    <span class="step-label">Delivered</span>
                </div>
            </div>

            <!-- Details Grid -->
            <div class="delivery-details-grid">
                <div class="detail-block">
                    <h5>${otherPartyLabel}</h5>
                    <p>${escapeHTML(otherPartyValue)}</p>
                    <small>${escapeHTML(otherPartySub)}</small>
                </div>
                <div class="detail-block">
                    <h5>Assigned Volunteer</h5>
                    <p>${del.volunteer?.assigned ? `🚴 ${escapeHTML(del.volunteer.name)}` : 'Assigning volunteer...'}</p>
                    <small>${del.volunteer?.assigned ? `📞 ${escapeHTML(del.volunteer.phone)} • ${escapeHTML(del.volunteer.location)}` : 'System dispatching'}</small>
                </div>
                <div class="detail-block">
                    <h5>Dijkstra Route</h5>
                    <p class="route-pill">🛣️ ${escapeHTML(del.route)}</p>
                    <small>Total Distance: <strong>${del.distanceKm} km</strong></small>
                </div>
            </div>

            <div class="delivery-action-footer">
                <div style="font-size:0.85rem; color:var(--text-muted);">
                    Pickup: <strong>${escapeHTML(del.pickupLocation)}</strong> ➔ Drop: <strong>${escapeHTML(del.deliveryLocation)}</strong>
                </div>
                <div>
                    ${nextActionBtn}
                </div>
            </div>
        </div>
    `;
}

// ================= INTERNAL STATUS ADVANCE =================
async function advanceDeliveryStatus(deliveryId) {
    try {
        const data = await apiRequest("/api/internal/deliveries/step", "POST", { deliveryId });
        showToast("success", `Delivery #${deliveryId} is now ${data.status}!`);

        if (currentRole === "donor") {
            loadDonorDeliveries();
            loadDonorOverview();
        } else if (currentRole === "ngo") {
            loadNgoDeliveries();
            loadNgoOverview();
        }
    } catch (err) {
        showToast("error", err.message);
    }
}

// ================= PUBLIC LANDING STATS =================
async function loadLandingStats() {
    try {
        const data = await apiRequest("/api/stats");
        if (data.success) {
            document.getElementById("landingMealsCount").textContent = `${Math.max(120, data.totalDonations * 25)}+`;
            document.getElementById("landingDonorsCount").textContent = `${data.totalDonors}+`;
            document.getElementById("landingNgosCount").textContent = `${data.totalNGOs}+`;
            document.getElementById("landingDeliveriesCount").textContent = `${data.totalDeliveries}+`;
        }
    } catch (err) {
        // silent fallback to default placeholder stats
    }
}

// ================= INITIALIZATION =================
document.addEventListener("DOMContentLoaded", async () => {
    loadLandingStats();

    const token = localStorage.getItem("foodrescue_token");
    if (!token) {
        showView("landingView");
        return;
    }

    // Validate token with server
    try {
        const data = await apiRequest("/api/auth/me");
        if (data.success && data.user) {
            currentUser = data.user;
            currentRole = data.user.role;

            if (currentRole === "donor") {
                setupDonorDashboard();
            } else if (currentRole === "ngo") {
                setupNgoDashboard();
            } else {
                showView("landingView");
            }
        } else {
            localStorage.removeItem("foodrescue_token");
            showView("landingView");
        }
    } catch (err) {
        localStorage.removeItem("foodrescue_token");
        showView("landingView");
    }
});
