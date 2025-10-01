#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/atomic.h>

LOG_MODULE_REGISTER(app);           /* usa CONFIG_LOG_DEFAULT_LEVEL */
#define HELLO_PERIOD_MS CONFIG_HELLO_PERIOD_MS

static struct k_timer hello_timer;
static atomic_t tick = ATOMIC_INIT(0);

static void hello_timer_cb(struct k_timer *timer)
{
    int t = atomic_inc(&tick);

    LOG_INF("Hello World! period=%dms tick=%d", HELLO_PERIOD_MS, t);
    LOG_DBG("Debug details: uptime=%u ms", (unsigned)k_uptime_get_32());

    if ((t % 5) == 0) {
        LOG_ERR("Simulated error (tick=%d). Demonstração de níveis de log.", t);
    }
}

static void hello_timer_stop_cb(struct k_timer *timer) { }

int main(void)
{
    k_timer_init(&hello_timer, hello_timer_cb, hello_timer_stop_cb);
    k_timer_start(&hello_timer, K_MSEC(HELLO_PERIOD_MS), K_MSEC(HELLO_PERIOD_MS));

    while (1) {
        k_sleep(K_SECONDS(1));
    }
}
